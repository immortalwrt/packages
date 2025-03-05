include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=open-app-filter
PKG_RELEASE:=1

PKG_SOURCE_URL:=https://github.com/destan19/OpenAppFilter.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2025-03-03
PKG_SOURCE_VERSION:=c0b5b22f29a8ee4aef8ac4eb04992da7b2d3fc21
PKG_MIRROR_HASH:=6073c2feaa58fac4b16547f3d1d450a7e132c88f78abc0e656d54cddc74d2ba0

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

MAKE_PATH:=open-app-filter/src
MAKE_VARS+= LIBS="-lm -lpthread -lubox -luci -lubus -ljson-c -lblobmsg_json"

define Build/Compile
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/oaf/src" modules

	$(call Build/Compile/Default)
endef

define Package/appfilter/conffiles
/etc/config/appfilter
/etc/config/user_info
endef

define Package/appfilter/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/open-app-filter/src/oafd $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/open-app-filter/files/gen_class.sh $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/open-app-filter/files/hnat.sh $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/open-app-filter/files/oaf_rule $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/etc/appfilter
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/open-app-filter/files/feature_cn.cfg $(1)/etc/appfilter/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/open-app-filter/files/feature_en.cfg $(1)/etc/appfilter/

	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/init.d
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/open-app-filter/files/appfilter.config $(1)/etc/config/appfilter
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/open-app-filter/files/user_info.config $(1)/etc/config/user_info
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/open-app-filter/files/appfilter.init $(1)/etc/init.d/appfilter
endef

$(eval $(call KernelPackage,oaf))
$(eval $(call BuildPackage,appfilter))
