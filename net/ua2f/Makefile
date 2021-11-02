# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 Xinyu Zhou <zhouxinyu1001@gmail.com>
# Copyright (C) 2021 Tianling Shen <cnsztl@immortalwrt.org>

include $(TOPDIR)/rules.mk

PKG_NAME:=ua2f
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Zxilly/UA2F.git
PKG_SOURCE_DATE:=2021-11-02
PKG_SOURCE_VERSION:=d4e4c4dfe1acb111c9883daaa8642f764df0665a
PKG_MIRROR_HASH:=b87b70206243a0f2ca6c79669f41ba33c9b8e3a0fbc0aaf254e2b5db722a3fa6

PKG_LICENSE:=GPL-3.0-only
PKG_LICENSE_FILE:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/ua2f
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  TITLE:=Change User-Agent to Fwords
  URL:=https://github.com/Zxilly/UA2F
  DEPENDS:=+ipset +iptables-mod-conntrack-extra +iptables-mod-nfqueue \
    +libnetfilter-conntrack +libnetfilter-queue
endef

define Package/ua2f/description
  Change User-agent to Fwords to prevent being checked by Dr.Com.
endef

define Package/ua2f/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ua2f $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/init.d $(1)/etc/uci-defaults
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/files/ua2f.config $(1)/etc/config/ua2f
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/files/ua2f.init $(1)/etc/init.d/ua2f
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/files/ua2f.uci $(1)/etc/uci-defaults/80-ua2f
endef

$(eval $(call BuildPackage,ua2f))
