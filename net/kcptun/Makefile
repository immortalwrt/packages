include $(TOPDIR)/rules.mk

PKG_NAME:=kcptun
PKG_VERSION:=20200321
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/xtaci/kcptun/tar.gz/v${PKG_VERSION}?
PKG_SOURCE_DATE:=2020-03-21
PKG_HASH:=450e586528bd7b2e586605e3a664f77ebd9baa869918fcc6d6a41f84d4cfb4fd

PKG_MAINTAINER:=Dengfeng Liu <liudf0716@gmail.com>, Chao Liu <expiron18@gmail.com>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE.md

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/xtaci/kcptun

GO_PKG_LDFLAGS:=-s -w
GO_PKG_LDFLAGS_X:=main.VERSION=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/kcptun-config
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=Kcptun Config Scripts
  URL:=https://github.com/xtaci/kcptun
  DEPENDS:=$(GO_ARCH_DEPENDS)
endef

define Package/kcptun-config/install
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/kcptun.config $(1)/etc/config/kcptun
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/kcptun.init $(1)/etc/init.d/kcptun
endef

define Package/kcptun/Default
  define Package/kcptun-$(1)
    SECTION:=net
    CATEGORY:=Network
    SUBMENU:=Web Servers/Proxies
    TITLE:=KCP-based Secure Tunnel $(1)
    URL:=https://github.com/xtaci/kcptun
    DEPENDS:=+kcptun-config
  endef

  define Package/kcptun-$(1)/description
    kcptun is a Stable & Secure Tunnel Based On KCP with N:M Multiplexing.
This package only contains kcptun $(1).
  endef

  define Package/kcptun-$(1)/install
		$$(call GoPackage/Package/Install/Bin,$$(PKG_INSTALL_DIR))

		$$(INSTALL_DIR) $$(1)/usr/bin
		$$(INSTALL_BIN) $$(PKG_INSTALL_DIR)/usr/bin/$(1) $$(1)/usr/bin/kcptun-$(1)
  endef
endef

$(eval $(call BuildPackage,kcptun-config))
KCPTUN_COMPONENTS:=server client
$(foreach component,$(KCPTUN_COMPONENTS), \
  $(eval $(call Package/kcptun/Default,$(component))) \
  $(eval $(call GoBinPackage,kcptun-$(component))) \
  $(eval $(call BuildPackage,kcptun-$(component))) \
)
