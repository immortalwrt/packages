# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=chinadns-ng
PKG_VERSION:=2024.10.14
PKG_RELEASE:=1

ifeq ($(ARCH),aarch64)
  PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl_noasm@aarch64-linux-musl@generic+v8a@fast+lto
  PKG_HASH:=914e8b66805b1804f6688dfcda3b67c7c45e5fc5e05afff4837450f8b67a8372
else ifeq ($(ARCH),arm)
  # Referred to golang/golang-values.mk
  ARM_CPU_FEATURES:=$(word 2,$(subst +,$(space),$(call qstrip,$(CONFIG_CPU_TYPE))))
  ifeq ($(ARM_CPU_FEATURES),)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@arm-linux-musleabi@generic+v5t+soft_float@fast+lto
    PKG_HASH:=9adfe309a41f21156cc5597333c42c36bc9e4e42eb1a71d18b92c39aed0340b2
  else ifneq ($(filter $(ARM_CPU_FEATURES),vfp vfpv2),)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@arm-linux-musleabi@generic+v6+soft_float@fast+lto
    PKG_HASH:=4881e4dc20a1a4b21bc0cc3c378da8d8004274929e5900d5246aece230eea4f8
  else
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@arm-linux-musleabihf@generic+v7a@fast+lto
    PKG_HASH:=5a47e56ef6fac90d22eabc766ffb817cb15fa3875b03ea2a4cd8a684b25b401a
  endif
else ifeq ($(ARCH),i386)
  ifneq ($(CONFIG_TARGET_x86_geode)$(CONFIG_TARGET_x86_legacy),)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@i386-linux-musl@i686@fast+lto
    PKG_HASH:=f29853387f51bdb4a993504a31933ece538f99365f3f3b46794caa75a3b653ba
  else
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@i386-linux-musl@pentium4@fast+lto
    PKG_HASH:=279415d9fab1e49bb4bf819270da0d57a9dcdc078cbd4b725b0b7cf3c52d2aba
  endif
else ifeq ($(ARCH),mips)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@mips-linux-musl@mips32+soft_float@fast+lto
    PKG_HASH:=b57f9ba76ff4a7c52d1cfbe75de47f6f0e8a1bf8f2a293a39c10b5d94c99cc0f
else ifeq ($(ARCH),mipsel)
  ifeq ($(CONFIG_HAS_FPU),)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32+soft_float@fast+lto
    PKG_HASH:=f0ca46e7ca83711ae24a6c0d7c71400d994dc7289cae599412fd8e654b198f3e
  else
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32@fast+lto
    PKG_HASH:=48eecd536e1f4cb7d3fa44cdc23d996acfbc75004d8e16b405a7ee148523696e
  endif
else ifeq ($(ARCH),x86_64)
  PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@x86_64-linux-musl@x86_64@fast+lto
  PKG_HASH:=6928e28f1c6c41099b6ce8ab1ce38a98cc9da75ff9533f8644f67be455463d0e
else
  PKG_SOURCE_URL_FILE:=dummy
  PKG_HASH:=dummy
endif

PKG_SOURCE:=$(subst $(PKG_NAME),$(PKG_NAME)-$(PKG_VERSION),$(PKG_SOURCE_URL_FILE))
PKG_SOURCE_URL:=https://github.com/zfl9/chinadns-ng/releases/download/$(PKG_VERSION)/

PKG_LICENSE:=AGPL-3.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

include $(INCLUDE_DIR)/package.mk

PKG_UNPACK:=:

define Package/chinadns-ng
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=IP Addresses and Names
  TITLE:=ChinaDNS next generation, refactoring with epoll and ipset.
  URL:=https://github.com/zfl9/chinadns-ng
  DEPENDS:=@(aarch64||arm||i386||mips||mipsel||x86_64)
endef

define Build/Compile
endef

define Package/chinadns-ng/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(DL_DIR)/$(PKG_SOURCE) $(1)/usr/bin/chinadns-ng
endef

$(eval $(call BuildPackage,chinadns-ng))
