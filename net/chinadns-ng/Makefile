# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=chinadns-ng
PKG_VERSION:=2025.03.27
PKG_RELEASE:=1

ifeq ($(ARCH),aarch64)
  PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl_noasm@aarch64-linux-musl@generic+v8a@fast+lto
  PKG_HASH:=0d6f5f742a3c81f907639b5e1ef2b727870f7aafc67010728e88a7968079b9c0
else ifeq ($(ARCH),arm)
  # Referred to golang/golang-values.mk
  ARM_CPU_FEATURES:=$(word 2,$(subst +,$(space),$(call qstrip,$(CONFIG_CPU_TYPE))))
  ifeq ($(ARM_CPU_FEATURES),)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@arm-linux-musleabi@generic+v5t+soft_float@fast+lto
    PKG_HASH:=2699f8649897e4b8f16f9abb9e27a8740fcf76284d11500471481bf5fb1c1a2c
  else ifneq ($(filter $(ARM_CPU_FEATURES),vfp vfpv2),)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@arm-linux-musleabi@generic+v6+soft_float@fast+lto
    PKG_HASH:=2d972e864a90d1c5e7c874e8ff1f1229fddc03e869c7be9f3b4bf4347a7f150a
  else
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@arm-linux-musleabihf@generic+v7a@fast+lto
    PKG_HASH:=77faf3fea926752e2ab54a4d32b3de1c29ada8e075921a0e5bb219285d34d938
  endif
else ifeq ($(ARCH),i386)
  ifneq ($(CONFIG_TARGET_x86_geode)$(CONFIG_TARGET_x86_legacy),)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@i386-linux-musl@i686@fast+lto
    PKG_HASH:=d9d0c3c38ca5b3ac266ae5753a0d87b37f571a6e2a8806699f858ad348afbf5e
  else
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@i386-linux-musl@pentium4@fast+lto
    PKG_HASH:=dd54f258239f9b868c67ec4e18de074706f8b852796bfd61178f2cd145d17ff6
  endif
else ifeq ($(ARCH),mips)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@mips-linux-musl@mips32+soft_float@fast+lto
    PKG_HASH:=b8ae32305069cccf01ef2704633ab326d69bd8ef7cfb71a30722d71e9cd6787e
else ifeq ($(ARCH),mipsel)
  ifeq ($(CONFIG_HAS_FPU),)
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32+soft_float@fast+lto
    PKG_HASH:=f12ce9b5227fefbf82401bd22379a52f2ec157c7cbe7e7dbdd2c0b2599e3a323
  else
    PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32@fast+lto
    PKG_HASH:=7cf942d7fac3cf1f86295ee1af8a724065c6ab6595ca084cbd9f5ecc34e32483
  endif
else ifeq ($(ARCH),riscv64)
  PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@riscv64-linux-musl@baseline_rv64@fast+lto
  PKG_HASH:=8bf3e88c78f537595651cb1ad40196c36d4bf5c1796ff70990523784409f8155
else ifeq ($(ARCH),x86_64)
  PKG_SOURCE_URL_FILE:=$(PKG_NAME)+wolfssl@x86_64-linux-musl@x86_64@fast+lto
  PKG_HASH:=37b337f1006b85176840f1b82508731a292751d1ee94bb3791578d04d63f856f
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
  DEPENDS:=@(aarch64||arm||i386||mips||mipsel||riscv64||x86_64)
endef

define Build/Compile
endef

define Package/chinadns-ng/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(DL_DIR)/$(PKG_SOURCE) $(1)/usr/bin/chinadns-ng
endef

$(eval $(call BuildPackage,chinadns-ng))
