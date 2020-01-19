include $(TOPDIR)/rules.mk

PKG_NAME:=shadowsocks-client
PKG_VERSION:=0.6.1
PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/zhao-gang/shadowsocks-tiny.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=f26951069e15fde443e2404e005e15445e1301fa
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
PKG_MIRROR_HASH:=a5083fd26054a7f0e597ead640dc97fc9d57f25f7607e9a582c74b2b4226c261
PKG_MAINTAINER:=Gang Zhao <gang.zhao.42@gmail.com>

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=COPYING

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/shadowsocks-client
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=shadowsocks client for router
  URL:=https://github.com/zhao-gang/shadowsocks-tiny
  DEPENDS:=+libopenssl
endef

define Package/shadowsocks-client/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/sslocal $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DATA) ./files/sslocal.config $(1)/etc/config/sslocal
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/sslocal.init $(1)/etc/init.d/sslocal
endef

$(eval $(call BuildPackage,shadowsocks-client))
