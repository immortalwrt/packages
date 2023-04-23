# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 Xinyu Zhou <zhouxinyu1001@gmail.com>
# Copyright (C) 2021 Tianling Shen <cnsztl@immortalwrt.org>

include $(TOPDIR)/rules.mk

PKG_NAME:=UA2F
PKG_VERSION:=4.0.3
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/Zxilly/UA2F/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=66d1225aa7bd55a54705841beed900e543ca8e232ca802fc8c8d08c1408d7d09

PKG_LICENSE:=GPL-3.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/ua2f
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  TITLE:=Change User-Agent to Fwords
  URL:=https://github.com/Zxilly/UA2F
  DEPENDS:=+iptables +iptables-mod-conntrack-extra \
    +iptables-mod-filter +iptables-mod-nfqueue \
    +libnetfilter-conntrack +libnetfilter-queue \
    +USE_GLIBC:libasan
endef

define Package/ua2f/description
  Change User-agent to Fwords to prevent being checked by Dr.Com.
endef

define Package/ua2f/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ua2f $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/init.d $(1)/etc/uci-defaults
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/openwrt/files/ua2f.config $(1)/etc/config/ua2f
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/openwrt/files/ua2f.init $(1)/etc/init.d/ua2f
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/openwrt/files/ua2f.uci $(1)/etc/uci-defaults/80-ua2f
endef

$(eval $(call BuildPackage,ua2f))
