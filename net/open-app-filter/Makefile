include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=open-app-filter
PKG_RELEASE:=1

PKG_SOURCE_URL:=https://github.com/destan19/OpenAppFilter.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2023-05-25
PKG_SOURCE_VERSION:=d9d8e8088c6ecdc8a2957ffe1002547a9f1c6c0d
PKG_MIRROR_HASH:=83545d1b2d1c047869c62c08417902c3b8c2c909ab65d57c1db58df357877223

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

RSTRIP:=:

define KernelPackage/oaf
  SECTION:=Kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Netfilter Extensions
  TITLE:=open app filter kernel module
  FILES:=$(PKG_BUILD_DIR)/oaf/src/oaf.ko
  DEPENDS:=+kmod-ipt-conntrack
  AUTOLOAD:=$(call AutoLoad,0,oaf)
endef

define Package/appfilter
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+libblobmsg-json +libjson-c +libpthread +libubox +libubus +libuci +kmod-oaf
  TITLE:=App filter userspace module
endef

define Build/Compile
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/oaf/src" modules
endef

define Package/appfilter/conffiles
/etc/config/appfilter
endef

define Package/appfilter/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/etc/appfilter $(1)/etc/config $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/open-app-filter/files/appfilter.sh $(1)/usr/bin/appfilter.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/open-app-filter/files/gen_class.sh $(1)/usr/bin/gen_class.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/open-app-filter/files/appfilter.lua $(1)/usr/bin/appfilter
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/open-app-filter/files/feature.cfg $(1)/etc/appfilter/feature.cfg
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/open-app-filter/files/appfilter.config $(1)/etc/config/appfilter
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/open-app-filter/files/appfilter.init $(1)/etc/init.d/appfilter
endef

$(eval $(call KernelPackage,oaf))
$(eval $(call BuildPackage,appfilter))
