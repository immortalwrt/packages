# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 Xinyu Zhou <zhouxinyu1001@gmail.com>
# Copyright (C) 2021 Tianling Shen <cnsztl@immortalwrt.org>

include $(TOPDIR)/rules.mk

PKG_NAME:=ua2f
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Zxilly/UA2F.git
PKG_SOURCE_DATE:=2022-03-05
PKG_SOURCE_VERSION:=d0aa9395d80b64a008a4bd85e292e4df8a85643f
PKG_MIRROR_HASH:=fedb93e61e489aee3c0546355b567975589d3d1417b69dc7a33ca4498635638b

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
