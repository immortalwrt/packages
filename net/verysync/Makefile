# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

ifeq ($(ARCH),aarch64)
  PKG_ARCH_VERYSYNC:=arm64
  PKG_HASH_VERYSYNC:=b5ecf097b47856e3e884bfe6f7a00a46f37f31466ac3aa4101c20e87672b65a4
else ifeq ($(ARCH),arm)
  PKG_ARCH_VERYSYNC:=arm
  PKG_HASH_VERYSYNC:=c7ceb85c0bf2df9a79987bc92fe2174140459a0864920f6d2c956011e34779a3
else ifeq ($(ARCH),i386)
  PKG_ARCH_VERYSYNC:=386
  PKG_HASH_VERYSYNC:=2dce24c9e6537ac50e1d3ba36efff04aeb0160b134444e98f69f6924bd4d38cb
else ifeq ($(ARCH),mips)
  PKG_ARCH_VERYSYNC:=mips
  PKG_HASH_VERYSYNC:=fdaf62e13f32f5a257c509ea53a89ec0b4bf72422106c941434087308d71fbd9
else ifeq ($(ARCH),mipsel)
  PKG_ARCH_VERYSYNC:=mipsle
  PKG_HASH_VERYSYNC:=0b3b621808be67bbdc2fdd6ba8b0fe7255cb2e1864f1f4873738660aa6055de0
else ifeq ($(ARCH),powerpc64)
  PKG_ARCH_VERYSYNC:=ppc64
  PKG_HASH_VERYSYNC:=ed1814149bef1378c0591a0cc05b0a5e25368b57ef0a183d021f0e67f1a7c6e6
else ifeq ($(ARCH),x86_64)
  PKG_ARCH_VERYSYNC:=amd64
  PKG_HASH_VERYSYNC:=4d1231b78b577ee0942e24228c4eff9b77ddc0891ea990cd0d430fd0fc097d0a
endif

PKG_NAME:=verysync
PKG_VERSION:=2.13.2
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
