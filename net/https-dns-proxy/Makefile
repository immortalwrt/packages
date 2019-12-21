include $(TOPDIR)/rules.mk

PKG_NAME:=https_dns_proxy
PKG_VERSION:=2019-12-03
PKG_RELEASE=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/aarond10/https_dns_proxy
PKG_SOURCE_DATE:=2019-12-03
PKG_SOURCE_VERSION:=2adeafb67cbe8d67148219c48334856ae4f3bd75
PKG_MIRROR_HASH:=58088baa092cd9634652d65f9b5650db88d2e102cb370710654db7b15f2f0e42

PKG_MAINTAINER:=Stan Grishin <stangri@melmac.net>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_OPTIONS += -DCLANG_TIDY_EXE=

define Package/https_dns_proxy
  SECTION:=net
  CATEGORY:=Network
  TITLE:=DNS over HTTPS Proxy Server
  DEPENDS:=+libcares +libcurl +libev +ca-bundle
endef

define Package/https_dns_proxy/install
	$(INSTALL_DIR) $(1)/usr/sbin $(1)/etc/init.d ${1}/etc/config
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/https_dns_proxy $(1)/usr/sbin/
	$(INSTALL_BIN) ./files/https_dns_proxy.init $(1)/etc/init.d/https_dns_proxy
	$(INSTALL_CONF) ./files/https_dns_proxy.config $(1)/etc/config/https_dns_proxy
endef

$(eval $(call BuildPackage,https_dns_proxy))
