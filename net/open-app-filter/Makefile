include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=open-app-filter
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_URL:=https://github.com/destan19/OpenAppFilter.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2022-06-21
PKG_SOURCE_VERSION:=7d4b72fd04bd41c8d74366cd75354610855be9a6
PKG_MIRROR_HASH:=bd84ad51fcaaeb21f8145294473ba9e3c0d02166270ad7dd5b53a0c683d4a52f

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
