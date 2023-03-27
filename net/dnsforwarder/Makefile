#
# Copyright (C) 2021 ImmortalWrt
# <https://immortalwrt.org>
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dnsforwarder
PKG_VERSION:=6.5.2
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/lifenjoiner/dnsforwarder.git
PKG_SOURCE_DATE:=2023-03-25
PKG_SOURCE_VERSION:=1ae31a0fbf255b02ed35760e3a1d88b8db320b3a
PKG_MIRROR_HASH:=79e4765c963e5a45509087a6605412b2c35d6bc0d449008332286f05e3565823

PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Dennis <openwrt@tossp.com>

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/dnsforwarder
  SECTION:=net
  CATEGORY:=Network
  TITLE:=A simple DNS forwarder
  URL:=https://github.com/holmium/dnsforwarder
  DEPENDS:=+coreutils +coreutils-base64 +dnsmasq-full +libpthread +wget-ssl
endef

define Package/dnsforwarder/description
  Forwarding queries to customized domains (and their subdomains) to specified servers
  over a specified protocol (UDP or TCP). non-standard ports are supported.
endef

CONFIGURE_ARGS+= --enable-downloader=wget

TARGET_CFLAGS += -ffunction-sections -fdata-sections -flto
TARGET_LDFLAGS += -Wl,--gc-sections,--as-needed -flto

define Package/dnsforwarder/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/dnsforwarder $(1)/usr/bin/dnsforwarder

	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) files/etc/config/dnsforwarder $(1)/etc/config/dnsforwarder
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) files/etc/init.d/dnsforwarder $(1)/etc/init.d/dnsforwarder

	$(INSTALL_DIR) $(1)/etc/dnsforwarder
	$(INSTALL_CONF) files/etc/dnsforwarder/gfw.txt $(1)/etc/dnsforwarder/gfw.txt
	$(INSTALL_DIR) $(1)/usr/share/dnsforwarder
	$(INSTALL_BIN) files/usr/share/dnsforwarder/gfwlist.sh $(1)/usr/share/dnsforwarder/gfwlist.sh
endef

$(eval $(call BuildPackage,dnsforwarder))
