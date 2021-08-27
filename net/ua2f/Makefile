# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 Zxilly <zhouxinyu1001@gmail.com>

include $(TOPDIR)/rules.mk

PKG_NAME:=ua2f
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Zxilly/UA2F.git
PKG_SOURCE_DATE:=2021-08-10
PKG_SOURCE_VERSION:=6fe0b262016da48446197a5e307a04a4e9b66612
PKG_MIRROR_HASH:=43d25d95fc16134b2b3f2ffae2b52af5b96fd9d0d450a5b468a8967ce981aa1b

PKG_LICENSE:=GPL-3.0-only
PKG_LICENSE_FILE:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

include $(INCLUDE_DIR)/package.mk

define Package/ua2f
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  TITLE:=Change User-Agent to Fwords
  URL:=https://github.com/Zxilly/UA2F
  DEPENDS:=+iptables-mod-nfqueue +libipset +libnetfilter-conntrack +libnetfilter-queue
endef

define Package/ua2f/description
  Change User-agent to Fwords to prevent being checked by Dr.Com.
endef

EXTRA_LDFLAGS+= -lmnl -lnetfilter_queue -lipset

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) $(EXTRA_LDFLAGS) \
		$(PKG_BUILD_DIR)/src/ua2f.c -o $(PKG_BUILD_DIR)/src/ua2f
endef

define Package/ua2f/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/ua2f $(1)/usr/bin

	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/init.d $(1)/etc/uci-defaults
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/files/ua2f.config $(1)/etc/config/ua2f
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/files/ua2f.init $(1)/etc/init.d/ua2f
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/files/ua2f.uci $(1)/etc/uci-defaults/80-ua2f
endef

$(eval $(call BuildPackage,ua2f))
