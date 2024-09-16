# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=chinadns-ng
PKG_VERSION:=2024.09.08
PKG_RELEASE:=1

ifeq ($(ARCH),aarch64)
  PKG_SOURCE:=$(PKG_NAME)+wolfssl_noasm@aarch64-linux-musl@generic+v8a@fast+lto
  PKG_HASH:=bac7fa5355b60e811092bbc0ba3f44512682087c5af0cd5ca5864bfe264d41ed
else ifeq ($(ARCH),arm)
  # Referred to golang/golang-values.mk
  ARM_CPU_FEATURES:=$(word 2,$(subst +,$(space),$(call qstrip,$(CONFIG_CPU_TYPE))))
  ifeq ($(ARM_CPU_FEATURES),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@arm-linux-musleabi@generic+v5t+soft_float@fast+lto
    PKG_HASH:=ad3fa0cac79bf0aa505df1b26e8249f39de7dbcd6ec96fe5efab7d30d712d61d
  else ifneq ($(filter $(ARM_CPU_FEATURES),vfp vfpv2),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@arm-linux-musleabi@generic+v6+soft_float@fast+lto
    PKG_HASH:=2e81cef3dae7e736fa98d6a4b2d654c5bbc2e13a0f128f22db564f4cac9a5283
  else
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@arm-linux-musleabihf@generic+v7a@fast+lto
    PKG_HASH:=7d4f53b8982b415f087fafefb2568a317a0c241d0f79d0cf07ce2de089b11256
  endif
else ifeq ($(ARCH),i386)
  ifneq ($(CONFIG_TARGET_x86_geode)$(CONFIG_TARGET_x86_legacy),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@i386-linux-musl@i686@fast+lto
    PKG_HASH:=7ad9528daceb81e7e4376d80a6956ca947e6d096f5d3fb3b46a97f64b1c06ddc
  else
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@i386-linux-musl@pentium4@fast+lto
    PKG_HASH:=1575c0f0223bb95693c3d1d690d6076f50ee91e90e089b422343bf3b403c0f8b
  endif
else ifeq ($(ARCH),mips)
  ifeq ($(CPU_TYPE),mips32)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mips-linux-musl@mips32+soft_float@fast+lto
    PKG_HASH:=e5784f4a4bded6a9856469a5d4605c15c1f6d02b13aeb1f46a38fa4f78537bbb
  else
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mips-linux-musl@mips32r2+soft_float@fast+lto
    PKG_HASH:=a8c0644d5c9715dadafa7890cd24a911718a71f58a4328b426cb9a239c1a2cde
  endif
else ifeq ($(ARCH),mipsel)
  ifeq ($(CPU_TYPE),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32+soft_float@fast+lto
    PKG_HASH:=129110ee8846323eeec7b44e0227b3b7a2a76cb493c30437a5d65be31e1289c9
  else ifeq ($(CONFIG_HAS_FPU),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32r2+soft_float@fast+lto
    PKG_HASH:=375453bc696e3cd11dda7476c99aaca0933f6f282a909a2220d459e4624ba550
  else
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32r2@fast+lto
    PKG_HASH:=fadbf0d08e154922431a29a1d5f63b0347e0728886a23f2fed836c0b908f07f8
  endif
else ifeq ($(ARCH),x86_64)
  PKG_SOURCE:=$(PKG_NAME)+wolfssl@x86_64-linux-musl@x86_64@fast+lto
  PKG_HASH:=862fa3efdb91cdbd9dacd74c6733a672e999410dbe9c6f2d48d479aae9454165
else
  PKG_SOURCE:=dummy
  PKG_HASH:=dummy
endif
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
