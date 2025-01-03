include $(TOPDIR)/rules.mk

PKG_NAME:=Cloak
PKG_VERSION:=2.10.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/cbeuw/Cloak/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=f9fcc78e967184421b415309cedf3bf9b2a880827bbc20890240dff4aa68eb12

PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Zxl hhyccc <zxlhhy@gmail.com>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/cbeuw/Cloak
GO_PKG_BUILD_PKG:=$(GO_PKG)/cmd/...
GO_PKG_LDFLAGS:=-s -w -X 'main.VERSION=$(PKG_VERSION)'

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/Cloak/install
	$(call GoPackage/Package/Install/Bin,$(PKG_INSTALL_DIR))

	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/$(2) $(1)/usr/bin/
endef

define Package/Cloak/template
  define Package/$(1)
    SECTION:=net
    CATEGORY:=Network
    SUBMENU:=Web Servers/Proxies
    TITLE:=$(1) - Cloak is a pluggable transport $(2)
    URL:=https://github.com/cbeuw/Cloak
    DEPENDS:=$(GO_ARCH_DEPENDS)
  endef

  define Package/$(1)/description
    $(1) Cloak is a pluggable transport for advanced censorship evasion.
  endef

  define Package/$(1)/install
    $(call Package/Cloak/install,$$(1),$(1))
  endef
endef

$(eval $(call Package/Cloak/template,ck-client,client))
$(eval $(call Package/Cloak/template,ck-server,server))
$(eval $(call BuildPackage,ck-client))
$(eval $(call BuildPackage,ck-server))
