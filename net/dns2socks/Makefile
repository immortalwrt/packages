# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=dns2socks
PKG_VERSION:=2.1
PKG_RELEASE:=2

PKG_SOURCE:=SourceCode.zip
PKG_SOURCE_URL:=@SF/dns2socks
PKG_SOURCE_DATE:=2020-02-18
PKG_HASH:=406b5003523577d39da66767adfe54f7af9b701374363729386f32f6a3a995f4

PKG_MAINTAINER:=ghostmaker
PKG_LICENSE:=BSD-3-Clause
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

UNZIP_CMD:=unzip -q -d $(PKG_BUILD_DIR) $(DL_DIR)/$(PKG_SOURCE)

define Package/dns2socks
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=IP Addresses and Names
  TITLE:=DNS to SOCKS or HTTP proxy
  URL:=http://dns2socks.sourceforge.net/
  DEPENDS:=+libpthread
endef

define Package/dns2socks/description
  This is a command line utility to resolve DNS requests via
  a SOCKS tunnel like Tor or a HTTP proxy.
endef

define Build/Compile
	$(TARGET_CC) \
	$(TARGET_CFLAGS) \
	$(TARGET_CPPFLAGS) \
	$(FPIC) \
	-o $(PKG_BUILD_DIR)/DNS2SOCKS/dns2socks \
	$(PKG_BUILD_DIR)/DNS2SOCKS/DNS2SOCKS.c \
	$(TARGET_LDFLAGS) -pthread
endef

define Package/dns2socks/conffiles
/etc/config/dns2socks
endef

define Package/dns2socks/preinst
#!/bin/sh
[ -n "$${IPKG_INSTROOT}" ] && exit 0
[ "$${PKG_UPGRADE}" = "1" ] && /etc/init.d/dns2socks stop > /dev/null 2>&1
exit 0
endef

define Package/dns2socks/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/DNS2SOCKS/dns2socks $(1)/usr/bin/dns2socks

	$(INSTALL_DIR) \
		$(1)/lib/upgrade/keep.d \
		$(1)/etc/init.d \
		$(1)/etc/config
	$(INSTALL_DATA) ./files/dns2socks.upgrade $(1)/lib/upgrade/keep.d/dns2socks
	$(INSTALL_BIN)  ./files/dns2socks.init    $(1)/etc/init.d/dns2socks
	$(INSTALL_CONF) ./files/dns2socks.config  $(1)/etc/config/dns2socks
endef

$(eval $(call BuildPackage,dns2socks))
