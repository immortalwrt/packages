# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 Zxilly <zhouxinyu1001@gmail.com>

include $(TOPDIR)/rules.mk

PKG_NAME:=ua2f
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Zxilly/UA2F.git
PKG_SOURCE_DATE:=2021-06-26
PKG_SOURCE_VERSION:=d82e7543e7ad45bb76ae0a3f4c6b704721bccc24
PKG_MIRROR_HASH:=5d5f3c893c21fb07eeba6663969a71e12da2ec3c47cc0cc012ca6168c9e1b9b0

PKG_LICENSE:=GPL-3.0-only
PKG_LICENSE_FILE:=LICENSE

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
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/init/ua2f $(1)/etc/init.d/ua2f
endef

$(eval $(call BuildPackage,ua2f))
