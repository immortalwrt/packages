# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=chinadns-ng
PKG_VERSION:=2024.05.12
PKG_RELEASE:=1

ifeq ($(ARCH),aarch64)
  PKG_SOURCE:=$(PKG_NAME)@aarch64-linux-musl@generic+v8a@fast+lto
  PKG_HASH:=5d09aab8dbea99935b864b8f2c569e95a4e7c23aad8f0b19860b145dc917106f
else ifeq ($(ARCH),arm)
  # Referred to golang/golang-values.mk
  ARM_CPU_FEATURES:=$(word 2,$(subst +,$(space),$(call qstrip,$(CONFIG_CPU_TYPE))))
  ifeq ($(ARM_CPU_FEATURES),)
    PKG_SOURCE:=$(PKG_NAME)@arm-linux-musleabi@generic+v5t+soft_float@fast+lto
    PKG_HASH:=5ad0e3b3e86c308b7d0aa2fbfb91e87aa8842bc89df8c85fc54a58d5398408e3
  else ifneq ($(filter $(ARM_CPU_FEATURES),vfp vfpv2),)
    PKG_SOURCE:=$(PKG_NAME)@arm-linux-musleabi@generic+v6+soft_float@fast+lto
    PKG_HASH:=34c80e973ce2b59185ad6771a280afd35b82941d08f072f46b620cf993b7eb94
  else
    PKG_SOURCE:=$(PKG_NAME)@arm-linux-musleabihf@generic+v7a@fast+lto
    PKG_HASH:=ceee46ac45c4f3228c22a0a56e623132a5ad5631f0ce6a2ea0d3a4002fa4480f
  endif
else ifeq ($(ARCH),i386)
  ifneq ($(CONFIG_TARGET_x86_geode)$(CONFIG_TARGET_x86_legacy),)
    PKG_SOURCE:=$(PKG_NAME)@i386-linux-musl@i686@fast+lto
    PKG_HASH:=a9af39f0a8781a596fd221e8e8285cc8d880865deb1cdd353274c7ac2df9865f
  else
    PKG_SOURCE:=$(PKG_NAME)@i386-linux-musl@pentium4@fast+lto
    PKG_HASH:=2ce5915489e2639a67e9ad786a998755fa2cd6ff8d75fac8e82a7471299e7e4a
  endif
else ifeq ($(ARCH),mips)
  ifneq ($(CONFIG_HAS_FPU),)
    PKG_SOURCE:=$(PKG_NAME)@mips-linux-musl@mips32r2@fast+lto
    PKG_HASH:=ef906ee162b552b1baa8a57f549b18400c01018869cf07b193a841b754bb0edb
  else
    PKG_SOURCE:=$(PKG_NAME)@mips-linux-musl@mips32r2+soft_float@fast+lto
    PKG_HASH:=de904ee3b5eacc7367d714f90ce385d22000078004c3827f05d5f2d4ff3c80b8
  endif
else ifeq ($(ARCH),mipsel)
  PKG_SOURCE:=$(PKG_NAME)@mipsel-linux-musl@mips32r2+soft_float@fast+lto
  PKG_HASH:=2149587515744223deec2355913a963136f4999e87b7baea49a3ff266f0f46d0
else ifeq ($(ARCH),x86_64)
  PKG_SOURCE:=$(PKG_NAME)@x86_64-linux-musl@x86_64@fast+lto
  PKG_HASH:=323e5aebba9d894e9f4f9adecad078092a4a54b8bb91f5468216386430f6c120
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
