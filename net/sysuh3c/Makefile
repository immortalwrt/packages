include $(TOPDIR)/rules.mk

PKG_NAME:=sysuh3c
PKG_RELEASE:=2

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/haswelliris/h3c.git
PKG_SOURCE_DATE:=2019-03-01
PKG_SOURCE_VERSION:=8a3e0b5a9a5d989e7d8b2105d09a394c3663e016
PKG_MIRROR_HASH:=27ea0affd6b4142827f95b19990a686266d524faaf0a84e588b1b2247a529052

PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

define Package/sysuh3c
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Campus Network
  TITLE:=H3C client
endef

define Package/sysuh3c/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/h3c $(1)/usr/sbin/sysuh3c
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/sysuh3c.config $(1)/etc/config/sysuh3c
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/sysuh3c.init $(1)/etc/init.d/sysuh3c
endef

$(eval $(call BuildPackage,sysuh3c))
