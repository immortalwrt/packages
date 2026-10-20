/*
 * hust-network-login (C 版)
 * 华中科技大学校园网（深澜 ePortal）自动登录，掉线 15 秒自动重连。
 *
 * 依赖：libcurl（HTTP）、libcrypto/libopenssl（RSA 大数运算）。
 * 配置：环境变量 HUST_NETWORK_LOGIN_USERNAME / HUST_NETWORK_LOGIN_PASSWORD，
 *       或命令行传配置文件路径（两行：第一行用户名，第二行密码）。
 *
 * 状态上报：全部走 ubus —— `ubus call hust-network-login status` 返回
 *           state / last_error / updated / running / pid / ubus（ubus 字段是控制面自检结果）；
 *           控制面状态变化另记一条 syslog（logread 可见）。PID 另写 .pid 文件。
 * 控制面：进程自己注册 ubus 对象 hust-network-login（uloop + libubus），
 *       页面与脚本直接 `ubus call hust-network-login status|reconnect`，
 *       不再依赖 rpcd 的 ucode 插件（插件加载失败会让页面彻底失能）。
 *       登录循环跑在单独的 worker 线程，主线程只跑 uloop 事件循环；
 *       连不上 ubusd / ubusd 重启导致对象消失时，每 5 秒重连并重新发布（自愈）。
 * 控制：SIGHUP = 中断当前 HTTP 传输并立刻重新认证（重连，不重启进程）；
 *       SIGTERM/SIGINT = 干净退出（写 state=stopped、删 pidfile、注销 ubus 对象）。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <stdarg.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include <pthread.h>
#include <curl/curl.h>
#include <openssl/bn.h>
#include <libubox/utils.h>
#include <libubox/blobmsg.h>
#include <libubus.h>

/* 在线探测地址：默认用轻量的 captive portal 检测地址（在线时返回 204 空响应），
 * 掉线时同样会被门户拦截并返回带 query string 的页面。
 * 可用环境变量 HUST_NETWORK_LOGIN_TEST_URL 覆盖。 */
static const char *test_url =
	"http://connect.rom.miui.com/generate_204,"
	"http://connectivitycheck.platform.hicloud.com/generate_204,"
	"http://www.baidu.com";
/* 在线检测间隔（秒），可用环境变量 HUST_NETWORK_LOGIN_CHECK_INTERVAL 覆盖 */
static int check_interval = 15;

/* PID 文件：给 init 脚本 / 其它工具找进程用（状态查询请走 ubus status） */
static const char *pid_file = "/tmp/run/hust-network-login.pid";
static char last_error[224];

/*
 * 控制标志（只由信号处理函数写入，async-signal-safe）：
 *   g_stop      SIGTERM/SIGINT → 干净退出
 *   g_reconnect SIGHUP         → 中断当前 HTTP 传输并立刻重新认证
 * 于是「重连」不需要重启进程，init 脚本/procd/LuCI 都能秒级触发。
 */
static volatile sig_atomic_t g_stop = 0;
static volatile sig_atomic_t g_reconnect = 0;

/* 凭据（worker 线程用，主线程启动时填好） */
static char username[128] = {0};
static char password[128] = {0};

/*
 * 共享状态快照：worker 线程写、ubus 回调（主线程）读，全部在 st_lock 里访问。
 * 临界区只做内存拷贝，不做任何 I/O，不会阻塞登录循环。
 */
static pthread_mutex_t st_lock = PTHREAD_MUTEX_INITIALIZER;
static char st_state[16] = "idle";
static char st_ubus[16] = "init";
static long st_updated = 0;

static pthread_t worker_tid;
static struct ubus_context *ubus_ctx = NULL;

static void sig_handler(int sig)
{
	if (sig == SIGHUP)
		g_reconnect = 1;
	else
		g_stop = 1;
}

/*
 * 记录最近一次错误：既进 syslog，也留给 Web 界面显示。
 * 被手动重连（SIGHUP）打断的传输不算错误，直接忽略。
 */
static void set_error(const char *fmt, ...)
{
	char buf[sizeof(last_error)];
	va_list ap;

	if (g_reconnect)
		return;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	pthread_mutex_lock(&st_lock);
	memcpy(last_error, buf, sizeof(last_error));
	pthread_mutex_unlock(&st_lock);

	syslog(LOG_ERR, "%s", buf);
}

/*
 * 更新内存快照（state / updated）。状态不再落盘：
 * 查询走 ubus status（内存快照），控制面状态由 ubus 字段 + syslog 暴露。
 * 状态：idle 启动中 / probe 探测中 / login 认证中 / online 已在线 /
 *       error 登录失败重试中 / stopped 已停止
 */
static void write_state(const char *state)
{
	pthread_mutex_lock(&st_lock);
	snprintf(st_state, sizeof(st_state), "%s", state);
	st_updated = (long)time(NULL);
	pthread_mutex_unlock(&st_lock);
}

/* 记录控制面状态（registered / no-object(N) / reconnecting / unavailable）：写进内存快照，
 * 由 ubus status 的 "ubus" 字段对外暴露；状态变化时另记一条 syslog，这样
 * 「页面读不到状态」时看 logread 就能分清是进程没跑、ubus 没连上、还是注册被 ubusd 拒了。
 * 状态没变就不重复刷日志。返回是否发生了变化。 */
static int set_ubus_state(const char *s)
{
	int changed;

	pthread_mutex_lock(&st_lock);
	changed = strcmp(st_ubus, s) != 0;
	if (changed)
		snprintf(st_ubus, sizeof(st_ubus), "%s", s);
	pthread_mutex_unlock(&st_lock);

	if (changed)
		syslog(LOG_INFO, "ubus control plane: %s", s);

	return changed;
}

/* procd 之外也让 init 脚本/其它工具能找到 PID（SIGHUP 重连用） */
static void write_pidfile(void)
{
	FILE *f = fopen(pid_file, "w");

	if (!f)
		return;

	fprintf(f, "%ld\n", (long)getpid());
	fclose(f);
}

/* 可被打断的睡眠：被 SIGHUP/SIGTERM 打断就立刻返回 */
static void sleep_interruptible(int seconds)
{
	while (seconds > 0 && !g_stop && !g_reconnect)
		seconds = sleep((unsigned int)seconds);
}

/* libcurl 进度回调：非 0 表示中断传输
 * （手动重连 SIGHUP、或收到 SIGTERM 要退出时，都让正在飞的请求立刻收摊） */
static int xferinfo_cb(void *p, curl_off_t dltotal, curl_off_t dlnow,
		       curl_off_t ultotal, curl_off_t ulnow)
{
	(void)p, (void)dltotal, (void)dlnow, (void)ultotal, (void)ulnow;
	return (g_reconnect || g_stop) ? 1 : 0;
}

/* 深澜 ePortal 的 RSA 公钥（e=10001, n=94dd2a86...，pageInfo 实测） */
#define MODULUS \
	"94dd2a8675fb779e6b9f7103698634cd400f27a154afa67af6166a43fc2641722" \
	"2a79506d34cacc7641946abda1785b7acf9910ad6a0978c91ec84d40b71d2891" \
	"379af19ffb333e7517e390bd26ac312fe940c340466b4a5d4af1d65c3b5944078" \
	"f96a1a51a5a53e4bc302818b7c9f63c4a1b07bd7d874cef1c3d4b2f5eb7871"
#define EXPONENT "10001"

/* 响应缓冲区 */
struct resp_buf {
	char *data;
	size_t len;
};

static size_t write_cb(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	struct resp_buf *buf = userdata;
	size_t n = size * nmemb;
	char *p = realloc(buf->data, buf->len + n + 1);
	if (!p)
		return 0;
	buf->data = p;
	memcpy(buf->data + buf->len, ptr, n);
	buf->len += n;
	buf->data[buf->len] = '\0';
	return n;
}

/* HTTP GET，返回响应体（调用者 free），失败返回 NULL；
 * code 回填最终的 HTTP 状态码（跟随重定向之后），可为 NULL */
static char *http_get(const char *url, long *code)
{
	CURL *curl = curl_easy_init();
	struct resp_buf buf = {0};
	char *result = NULL;
	long status = 0;

	if (!curl)
		return NULL;

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
	curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfo_cb);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "hust-network-login");
	/* 跟随重定向：未登录时门户常把探测请求 302 到门户页，
	 * 不跟的话拿到的只是个空 body，会被误判成「已在线」 */
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);

	if (curl_easy_perform(curl) == CURLE_OK) {
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
		result = buf.data ? buf.data : malloc(1);
		if (result && !buf.data)
			result[0] = '\0';
	} else {
		free(buf.data);
	}

	if (code)
		*code = status;

	curl_easy_cleanup(curl);
	return result;
}

/* HTTP POST，返回响应体（调用者 free），失败返回 NULL */
static char *http_post(const char *url, const char *body)
{
	CURL *curl = curl_easy_init();
	struct resp_buf buf = {0};
	char *result = NULL;
	struct curl_slist *headers = NULL;

	if (!curl)
		return NULL;

	headers = curl_slist_append(headers,
		"Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
	headers = curl_slist_append(headers, "Accept: */*");

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
	curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfo_cb);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "hust-network-login");

	if (curl_easy_perform(curl) == CURLE_OK && buf.data)
		result = buf.data;
	else
		free(buf.data);

	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);
	return result;
}

/*
 * RSA 加密：c = BE(password ">" mac) ^ e mod n，输出小写 hex，左补零到 256 字符。
 * 等价于 Rust 的 BigUint::from_bytes_be(...).modpow(65537, n)。
 */
static char *encrypt_pass(const char *password, const char *mac)
{
	char msg[256];
	BIGNUM *e = NULL, *n = NULL, *m = NULL, *c = NULL;
	BN_CTX *ctx = NULL;
	char *hex = NULL, *out = NULL;
	size_t len, zeros, i;

	snprintf(msg, sizeof(msg), "%s>%s", password, mac);

	ctx = BN_CTX_new();
	c = BN_new();
	BN_hex2bn(&e, EXPONENT);
	BN_hex2bn(&n, MODULUS);
	m = BN_bin2bn((const unsigned char *)msg, (int)strlen(msg), NULL);

	BN_mod_exp(c, m, e, n, ctx);

	hex = BN_bn2hex(c); /* 大写，无前导零 */
	len = strlen(hex);
	zeros = (len < 256) ? (256 - len) : 0;

	out = malloc(257);
	memset(out, '0', zeros);
	for (i = 0; i < len; i++)
		out[zeros + i] = (char)tolower((unsigned char)hex[i]);
	out[256] = '\0';

	OPENSSL_free(hex);
	BN_free(e);
	BN_free(n);
	BN_free(m);
	BN_free(c);
	BN_CTX_free(ctx);
	return out;
}

/* URL 编码（等价 Rust urlencoding::encode，大写 hex） */
static char *url_encode(const char *s)
{
	static const char hex[] = "0123456789ABCDEF";
	size_t len = strlen(s), i, o = 0;
	char *out = malloc(len * 3 + 1);

	for (i = 0; i < len; i++) {
		unsigned char c = (unsigned char)s[i];
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			out[o++] = (char)c;
		} else {
			out[o++] = '%';
			out[o++] = hex[c >> 4];
			out[o++] = hex[c & 0xF];
		}
	}
	out[o] = '\0';
	return out;
}

/* 提取 prefix 与 suffix 之间的子串 */
static int extract(const char *text, const char *prefix, const char *suffix,
		   char *out, size_t outlen)
{
	const char *l = strstr(text, prefix);
	const char *r;
	size_t n;

	if (!l)
		return -1;
	l += strlen(prefix);
	r = strstr(l, suffix);
	if (!r)
		return -1;
	n = (size_t)(r - l);
	if (n >= outlen)
		return -1;
	memcpy(out, l, n);
	out[n] = '\0';
	return 0;
}

/* 去掉字符串末尾的 \r \n */
static void trim_crlf(char *s)
{
	size_t n = strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
		s[--n] = '\0';
}


/* 依次探测多个候选地址（逗号分隔），返回第一个「有效」响应体（调用者 free），
 * 全失败返回 NULL。
 * 有效 = 拿到非空内容，或标准 204（在线时 generate_204 的合法应答）。
 * 空 body 的其它状态（如门户对探测地址直接回 302/空页）没有任何可解析的
 * 门户标志，不能当成「已在线」，继续试下一个候选地址。 */
static char *probe(void)
{
	const char *p = test_url;

	while (*p) {
		char url[256];
		size_t i = 0;
		char *u, *resp;
		long code = 0;

		while (*p && *p != ',' && i < sizeof(url) - 1)
			url[i++] = *p++;
		url[i] = '\0';

		u = url;
		while (*u == ' ')
			u++;

		if (*u) {
			resp = http_get(u, &code);
			if (resp && (resp[0] || code == 204))
				return resp;
			syslog(LOG_WARNING, "probe %s got no usable response (http %ld), trying next",
			       u, code);
			free(resp);
		}

		if (*p == ',')
			p++;
	}

	return NULL;
}

/* 一次登录：返回 0 表示已在线或登录成功，非 0 表示失败 */
static int login(const char *username, const char *password)
{
	char *resp, *enc, *qs_enc, *login_resp;
	char portal_ip[64], mac[128], query_string[1024];
	char body[4096], login_url[160];
	int ok = -1;

	write_state("probe");

	resp = probe();
	if (!resp) {
		set_error("all probe urls failed");
		return -1;
	}

	/* 响应不含门户标志 => 已在线 */
	if (!strstr(resp, "/eportal/index.jsp") &&
	    !strstr(resp, "<script>top.self.location.href='http://")) {
		free(resp);
		return 0;
	}

	if (extract(resp, "<script>top.self.location.href='http://",
		    "/eportal/index.jsp", portal_ip, sizeof(portal_ip)) != 0) {
		set_error("extract portal_ip failed");
		free(resp);
		return -1;
	}

	if (extract(resp, "mac=", "&t=", mac, sizeof(mac)) != 0) {
		set_error("extract mac failed");
		free(resp);
		return -1;
	}

	if (extract(resp, "/eportal/index.jsp?", "'</script>\r\n",
		    query_string, sizeof(query_string)) != 0) {
		set_error("extract query_string failed");
		free(resp);
		return -1;
	}

	enc = encrypt_pass(password, mac);
	qs_enc = url_encode(query_string);

	if (snprintf(body, sizeof(body),
		     "userId=%s&password=%s&service=&queryString=%s&passwordEncrypt=true",
		     username, enc, qs_enc) >= (int)sizeof(body)) {
		set_error("login request body too large");
		free(enc);
		free(qs_enc);
		free(resp);
		return -1;
	}

	snprintf(login_url, sizeof(login_url),
		 "http://%s/eportal/InterFace.do?method=login", portal_ip);

	write_state("login");

	login_resp = http_post(login_url, body);
	if (login_resp) {
		syslog(LOG_INFO, "login resp: %.200s", login_resp);
		ok = strstr(login_resp, "success") ? 0 : -1;
		if (ok != 0)
			set_error("login rejected: %.160s", login_resp);
		free(login_resp);
	}
	else {
		set_error("login request failed");
	}

	free(enc);
	free(qs_enc);
	free(resp);
	return ok;
}

static int read_conf(const char *path, char *username, char *password)
{
	FILE *f = fopen(path, "r");
	if (!f)
		return -1;
	if (!fgets(username, 128, f) || !fgets(password, 128, f)) {
		fclose(f);
		return -1;
	}
	fclose(f);
	trim_crlf(username);
	trim_crlf(password);
	return 0;
}

/* ---------------------------------------------------------------------------
 * 登录循环（worker 线程）—— 原来的主循环原样搬进来，认证/加密逻辑零改动
 * ------------------------------------------------------------------------- */
static void *login_worker(void *arg)
{
	(void)arg;

	/*
	 * 主线程为了把信号「留给 worker」而屏蔽了 SIGHUP/SIGTERM/SIGINT，
	 * 而新线程会继承创建者的信号掩码 —— 所以这里必须显式解除屏蔽，
	 * 否则所有信号都会一直处于 pending，进程既不能重连也停不下来。
	 */
	{
		sigset_t set;

		sigemptyset(&set);
		sigaddset(&set, SIGHUP);
		sigaddset(&set, SIGTERM);
		sigaddset(&set, SIGINT);
		pthread_sigmask(SIG_UNBLOCK, &set, NULL);
	}

	while (!g_stop) {
		int rc;

		g_reconnect = 0; /* 消费掉上一次重连请求 */
		rc = login(username, password);

		if (g_stop)
			break;

		if (rc == 0) {
			syslog(LOG_INFO, "login ok, awaiting");
			pthread_mutex_lock(&st_lock);
			last_error[0] = '\0';
			pthread_mutex_unlock(&st_lock);
			write_state("online");
			sleep_interruptible(check_interval);
		} else if (g_reconnect) {
			/* 手动重连打断的，不是错误：立刻进入下一轮 */
			syslog(LOG_INFO, "reconnect requested, restarting cycle");
		} else {
			syslog(LOG_ERR, "login failed, retry in 1s");
			write_state("error");
			sleep_interruptible(1);
		}
	}

	write_state("stopped");
	unlink(pid_file);

	return NULL;
}

/* ---------------------------------------------------------------------------
 * ubus 控制面：对象 hust-network-login，方法 status / reconnect
 *
 * 字段与返回结构与原来的 rpcd ucode 插件逐字一致，LuCI 页面因此不用改：
 *   status    → { state, last_error, updated, running, pid }
 *   reconnect → { result, action, pid[, error] }
 * 特别注意 result 必须是**布尔**：视图里写的是 expect: { result: false }，
 * 换成字符串会被前端 expect 逻辑替换成 false（按钮就会一直报失败）。
 * ------------------------------------------------------------------------- */
/*
 * ubus 回复里的布尔值必须用 BLOBMSG_TYPE_BOOL（JSON 里是 true/false），
 * 不能用 blobmsg_add_u8 —— 那是 INT8，序列化成 0/1 数字。LuCI 视图里写的是
 * expect: { result: false }，前端 rpc.js 会把类型不符的值直接替换成 false，
 * 于是「重连」按钮就会永远报失败。
 */
static void blobmsg_add_boolean(struct blob_buf *buf, const char *name, bool val)
{
	uint8_t v = val ? 1 : 0;

	blobmsg_add_field(buf, BLOBMSG_TYPE_BOOL, name, &v, 1);
}

static int ubus_method_status(struct ubus_context *ctx, struct ubus_object *obj,
			      struct ubus_request_data *req, const char *method,
			      struct blob_attr *msg)
{
	struct blob_buf bb;
	char state[sizeof(st_state)];
	char err[sizeof(last_error)];
	char ub[sizeof(st_ubus)];
	long updated;

	(void)obj; (void)method; (void)msg;

	pthread_mutex_lock(&st_lock);
	snprintf(state, sizeof(state), "%s", st_state);
	snprintf(err, sizeof(err), "%s", last_error);
	snprintf(ub, sizeof(ub), "%s", st_ubus);
	updated = st_updated;
	pthread_mutex_unlock(&st_lock);

	memset(&bb, 0, sizeof(bb));
	blob_buf_init(&bb, 0);

	blobmsg_add_string(&bb, "state", state);
	blobmsg_add_string(&bb, "last_error", err);
	blobmsg_add_u64(&bb, "updated", (uint64_t)updated);
	blobmsg_add_boolean(&bb, "running", true);
	blobmsg_add_u32(&bb, "pid", (uint32_t)getpid());
	blobmsg_add_string(&bb, "ubus", ub);

	ubus_send_reply(ctx, req, bb.head);
	blob_buf_free(&bb);

	return 0;
}

static int ubus_method_reconnect(struct ubus_context *ctx, struct ubus_object *obj,
				 struct ubus_request_data *req, const char *method,
				 struct blob_attr *msg)
{
	struct blob_buf bb;
	int rc;

	(void)obj; (void)method; (void)msg;

	g_reconnect = 1;

	/* 把 SIGHUP 直接投给 worker 线程：复用现成的打断链路
	 * （xferinfo 回调中止 curl 传输 + sleep_interruptible 提前返回），
	 * 因此是秒级生效，且不重启进程、不碰认证代码。 */
	rc = pthread_kill(worker_tid, SIGHUP);

	memset(&bb, 0, sizeof(bb));
	blob_buf_init(&bb, 0);

	blobmsg_add_boolean(&bb, "result", rc == 0);
	blobmsg_add_string(&bb, "action", "signal");
	blobmsg_add_u32(&bb, "pid", (uint32_t)getpid());

	if (rc != 0)
		blobmsg_add_string(&bb, "error", strerror(rc));

	ubus_send_reply(ctx, req, bb.head);
	blob_buf_free(&bb);

	syslog(LOG_INFO, "reconnect requested via ubus (rc=%d)", rc);

	return 0;
}

static const struct ubus_method ubus_methods[] = {
	UBUS_METHOD_NOARG("status", ubus_method_status),
	UBUS_METHOD_NOARG("reconnect", ubus_method_reconnect),
};

static struct ubus_object_type ubus_obj_type =
	UBUS_OBJECT_TYPE("hust-network-login", ubus_methods);

static struct ubus_object ubus_obj = {
	.name = "hust-network-login",
	.type = &ubus_obj_type,
	.methods = ubus_methods,
	.n_methods = ARRAY_SIZE(ubus_methods),
};

/* ---------------------------------------------------------------------------
 * 控制面韧性：连接/注册失败不是终态
 *
 * 页面报 -32000「Object not found」（uhttpd 的 ubus 插件在 ubus_lookup_id()
 * 失败时抛的，在 ACL 校验之前）只可能是两种处境：进程根本没在跑（页面显示
 * 「服务未运行」），或者进程在跑但对象不在总线上 —— 后者必须在这里自愈：
 *   1. 启动时 ubusd 还没就绪（或刚好在重启）；
 *   2. ubusd 中途重启：连接断开、对象从总线消失。libubus 默认的
 *      connection_lost 只是 uloop_end()，进程还活着、对象却再也不回来了，
 *      于是页面从此一直报「Object not found」。
 * 所以统一走「定时重试」：连不上/注册失败每 UBUS_RETRY_MS 重试一次；断线后
 * 重连并重新发布对象（ubusd 换了实例，旧的 object/type id 已失效，必须清 0
 * 让它重新 push 类型）。
 * ------------------------------------------------------------------------- */
#define UBUS_RETRY_MS 5000

/* NULL = 用 libubus 编译期默认路径（/var/run/ubus/ubus.sock） */
static const char *ubus_socket_path;

static void ubus_attach(void);
static void ubus_retry_cb(struct uloop_timeout *tmo);

static struct uloop_timeout ubus_retry_tmo = { .cb = ubus_retry_cb };

static void ubus_retry_cb(struct uloop_timeout *tmo)
{
	(void)tmo;
	ubus_attach();
}

/* 连接断了（ubusd 重启/被杀）：不调 uloop_end()（那只是停掉事件循环），
 * 而是安排重连 + 重新注册 */
static void ubus_connection_lost(struct ubus_context *ctx)
{
	(void)ctx;

	if (set_ubus_state("reconnecting"))
		syslog(LOG_WARNING, "lost connection to ubusd, reconnecting in %d s",
		       UBUS_RETRY_MS / 1000);

	uloop_timeout_set(&ubus_retry_tmo, UBUS_RETRY_MS);
}

/* 连接 ubusd + 注册对象；任何一步失败都排一次重试，函数本身可反复调用 */
static void ubus_attach(void)
{
	int rc;

	/*
	 * 旧连接已经不可用（ubusd 重启/被杀）时，直接把 context 丢掉重建一个，
	 * 不走 ubus_reconnect()：它只负责把 socket 接回来，接回来之后 libubus 会在
	 * ubus_refresh_state() 里自己重新发布对象，我们再 add 一次就撞名了
	 * （实测：对象在总线上，但 add 返回 Invalid argument、调用方超时）；
	 * 而且它的结果我们也拿不到。重建之后注册路径只剩一条，可验证。
	 */
	if (ubus_ctx) {
		ubus_free(ubus_ctx);
		ubus_ctx = NULL;
	}

	/* ubusd 上的 object/type id 已经作废，清 0 让它重新发布 */
	ubus_obj.id = 0;
	ubus_obj_type.id = 0;

	ubus_ctx = ubus_connect(ubus_socket_path);
	if (!ubus_ctx) {
		if (set_ubus_state("unavailable"))
			syslog(LOG_WARNING, "cannot connect to ubusd, retrying in %d s",
			       UBUS_RETRY_MS / 1000);

		uloop_timeout_set(&ubus_retry_tmo, UBUS_RETRY_MS);
		return;
	}

	/* 覆盖 libubus 默认的 connection_lost（它只会 uloop_end()） */
	ubus_ctx->connection_lost = ubus_connection_lost;
	ubus_add_uloop(ubus_ctx);

	rc = ubus_add_object(ubus_ctx, &ubus_obj);
	if (rc == 0) {
		set_ubus_state("registered");
		syslog(LOG_INFO, "ubus object hust-network-login registered");
	}
	else {
		/* 错误码同时进 syslog 和 ubus status 的 ubus 字段，方便一眼看懂
		 * （6=权限不足，通常是 ubusd 的 ACL 不允许该用户注册对象） */
		char buf[24];

		snprintf(buf, sizeof(buf), "no-object(%d)", rc);
		if (set_ubus_state(buf))
			syslog(LOG_WARNING, "cannot register ubus object hust-network-login: %s",
			       ubus_strerror(rc));

		uloop_timeout_set(&ubus_retry_tmo, UBUS_RETRY_MS);
	}
}

int main(int argc, char **argv)
{
	openlog("hust-network-login", LOG_PID | LOG_NDELAY, LOG_DAEMON);

	/* SIGTERM/SIGINT = 干净退出；SIGHUP = 中断当前请求并立刻重新认证（重连不重启进程） */
	{
		struct sigaction sa;
		sigset_t set;

		memset(&sa, 0, sizeof(sa));
		sa.sa_handler = sig_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0; /* 不设 SA_RESTART，让 sleep() 能被打断 */

		sigaction(SIGHUP, &sa, NULL);
		sigaction(SIGTERM, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);

		/*
		 * 主线程屏蔽这三个信号，让它们只投递给 worker 线程：
		 * ubus 的 reconnect 用 pthread_kill(worker, SIGHUP) 就能精准打断
		 * worker 里阻塞中的 curl 传输；否则信号可能落在主线程，重连要等
		 * 当前请求超时（最长 10 秒）才生效。
		 */
		sigemptyset(&set);
		sigaddset(&set, SIGHUP);
		sigaddset(&set, SIGTERM);
		sigaddset(&set, SIGINT);
		pthread_sigmask(SIG_BLOCK, &set, NULL);
	}

	{
		const char *tu = getenv("HUST_NETWORK_LOGIN_TEST_URL");
		const char *ci = getenv("HUST_NETWORK_LOGIN_CHECK_INTERVAL");
		if (tu && tu[0])
			test_url = tu;
		if (ci && ci[0]) {
			int v = atoi(ci);
			if (v > 0)
				check_interval = v;
		}
	}

	if (argc >= 2) {
		if (read_conf(argv[1], username, password) != 0) {
			set_error("failed to read config file: %s", argv[1]);
			write_state("error");
			return 1;
		}
	} else {
		const char *u = getenv("HUST_NETWORK_LOGIN_USERNAME");
		const char *p = getenv("HUST_NETWORK_LOGIN_PASSWORD");
		if (u)
			strncpy(username, u, sizeof(username) - 1);
		if (p)
			strncpy(password, p, sizeof(password) - 1);
	}

	if (!username[0] || !password[0]) {
		set_error("no username/password configured");
		write_state("error");
		fprintf(stderr,
			"no username/password. usage: %s [config_file]\n"
			"  config file: line1=username, line2=password\n"
			"  or env: HUST_NETWORK_LOGIN_USERNAME / HUST_NETWORK_LOGIN_PASSWORD\n",
			argv[0]);
		return 1;
	}

	curl_global_init(CURL_GLOBAL_ALL);

	write_pidfile();
	write_state("idle");

	/* 登录循环放进 worker 线程，主线程腾出来跑 ubus */
	if (pthread_create(&worker_tid, NULL, login_worker, NULL) != 0) {
		syslog(LOG_ERR, "cannot start worker thread");
		write_state("stopped");
		unlink(pid_file);
		return 1;
	}

	/*
	 * 主线程：连接 ubusd、发布对象，然后跑事件循环。
	 * 连不上 ubusd 不影响登录（只是控制面不可用），ubus_attach() 会自己定时重试，
	 * 所以这里不需要区分成功/失败。
	 * socket 默认用 libubus 的编译期路径（/var/run/ubus/ubus.sock）；
	 * HUST_NETWORK_LOGIN_UBUS_SOCKET 可覆盖，方便在开发机上做离线测试。
	 */
	{
		const char *sock = getenv("HUST_NETWORK_LOGIN_UBUS_SOCKET");

		ubus_socket_path = (sock && sock[0]) ? sock : NULL;
	}

	ubus_attach();

	/* 500ms 粒度轮询而不是 uloop_run()：这样 ubus 重连定时器能跑到，
	 * 而且 worker 退出/收到信号后进程能自己结束 */
	while (!g_stop)
		uloop_run_timeout(500);

	pthread_join(worker_tid, NULL);

	if (ubus_ctx) {
		ubus_free(ubus_ctx);
		uloop_done();
	}

	curl_global_cleanup();
	syslog(LOG_INFO, "stopped");
	closelog();

	return 0;
}
