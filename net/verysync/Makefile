# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2022 ImmortalWrt.org

include $(TOPDIR)/rules.mk

ifeq ($(ARCH),aarch64)
  PKG_ARCH_VERYSYNC:=arm64
  PKG_HASH_VERYSYNC:=d55f8ada7466104dfcb596def7b08fec35b2933f4baad8c4ec269e48f7b5301e
else ifeq ($(ARCH),arm)
  PKG_ARCH_VERYSYNC:=arm
  PKG_HASH_VERYSYNC:=e53c3ab453beb9c67524dd72d02ffc771885441d746e365445bbc27bafca827e
else ifeq ($(ARCH),i386)
  PKG_ARCH_VERYSYNC:=386
  PKG_HASH_VERYSYNC:=1d3552bf96665c86387437030affb236e041ab4ebcb16f5673858f3a2c38eb2b
else ifeq ($(ARCH),mips)
  PKG_ARCH_VERYSYNC:=mips
  PKG_HASH_VERYSYNC:=6028c33f310a8242b047f640bfe11175622e8fea16b10dfab9a18dc3ad7a8013
else ifeq ($(ARCH),mipsel)
  PKG_ARCH_VERYSYNC:=mipsle
  PKG_HASH_VERYSYNC:=066a63a21c8c77a4c7078c98c8087d7af90fc61470aa374f60ed7729b20669c0
else ifeq ($(ARCH),powerpc64)
  PKG_ARCH_VERYSYNC:=ppc64
  PKG_HASH_VERYSYNC:=bf7e6b5b97fd58b64689d8458e98deb484b1a954fbf64c71d3e81b926cfef4e3
else ifeq ($(ARCH),x86_64)
  PKG_ARCH_VERYSYNC:=amd64
  PKG_HASH_VERYSYNC:=022ba95c408397f2319c8da589f844c7fb014bc03f5a7275f6f85390c78a471b
endif

PKG_NAME:=verysync
PKG_VERSION:=2.15.0
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-linux-$(PKG_ARCH_VERYSYNC)-v$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://dl.verysync.com/releases/v$(PKG_VERSION)/ \
		http://dl-cn.verysync.com/releases/v$(PKG_VERSION)/
PKG_HASH:=$(PKG_HASH_VERYSYNC)
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-linux-$(PKG_ARCH_VERYSYNC)-v$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/verysync
  SECTION:=net
  CATEGORY:=Network
  TITLE:=A efficient data transmission tool
  URL:=http://www.verysync.com
  DEPENDS:=@(aarch64||arm||i386||mips||mipsel||powerpc64||x86_64)
endef

define Build/Compile
endef

define Package/verysync/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/verysync $(1)/usr/bin/verysync
endef

$(eval $(call BuildPackage,verysync))
