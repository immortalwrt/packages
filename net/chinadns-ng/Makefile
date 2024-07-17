# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=chinadns-ng
PKG_VERSION:=2024.07.16
PKG_RELEASE:=1

ifeq ($(ARCH),aarch64)
  PKG_SOURCE:=$(PKG_NAME)+wolfssl_noasm@aarch64-linux-musl@generic+v8a@fast+lto
  PKG_HASH:=a3706e49aa71c113710a4d28fca5f1201708feb82002c26a3c8bf6a333cbaea7
else ifeq ($(ARCH),arm)
  # Referred to golang/golang-values.mk
  ARM_CPU_FEATURES:=$(word 2,$(subst +,$(space),$(call qstrip,$(CONFIG_CPU_TYPE))))
  ifeq ($(ARM_CPU_FEATURES),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@arm-linux-musleabi@generic+v5t+soft_float@fast+lto
    PKG_HASH:=8cb055798f6ef5d3480e94c5a9dbfe00ce91f4e9fd3be8b104d256a0c929107b
  else ifneq ($(filter $(ARM_CPU_FEATURES),vfp vfpv2),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@arm-linux-musleabi@generic+v6+soft_float@fast+lto
    PKG_HASH:=c5fe700241eeb4c4637369c761df7b255a4c171e89eda2ac4fb4f0fffe4b75df
  else
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@arm-linux-musleabihf@generic+v7a@fast+lto
    PKG_HASH:=ac4263c0b0231e3907141ac9440077a0f2c2db519d2307a875a5c6bf9107b338
  endif
else ifeq ($(ARCH),i386)
  ifneq ($(CONFIG_TARGET_x86_geode)$(CONFIG_TARGET_x86_legacy),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@i386-linux-musl@i686@fast+lto
    PKG_HASH:=a96ccab681f3987f45a7a509fde2b36f1aea35cd861376a4abd7bc6e5627d0cb
  else
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@i386-linux-musl@pentium4@fast+lto
    PKG_HASH:=d8762fdad735d03ccf5f3448cfffe15e2298779849eb32d928099b547a641868
  endif
else ifeq ($(ARCH),mips)
  ifeq ($(CPU_TYPE),mips32)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mips-linux-musl@mips32+soft_float@fast+lto
    PKG_HASH:=f706b5f79f3467d9f7f224759f8d62033027ed20ce5b3ef4e8551a373bce153e
  else
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mips-linux-musl@mips32r2+soft_float@fast+lto
    PKG_HASH:=739dae2a1c4e69017fa7db7732a4c02c2b03d56963035704dc951cc344ed724e
  endif
else ifeq ($(ARCH),mipsel)
  ifeq ($(CPU_TYPE),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32+soft_float@fast+lto
    PKG_HASH:=4eddf913452ac0862e258d619bb4f735333d2360ba8bd198489280673fe28846
  else ifeq ($(CONFIG_HAS_FPU),)
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32r2+soft_float@fast+lto
    PKG_HASH:=c8ae314a95a20a353394c2eb05638527b98222083a975da7cc3ecba270f2a0a5
  else
    PKG_SOURCE:=$(PKG_NAME)+wolfssl@mipsel-linux-musl@mips32r2@fast+lto
    PKG_HASH:=9863ab7b84bf0cf0f8210f4bbb844363cb8d703ff3b7e9a753aa2ec8dd166b46
  endif
else ifeq ($(ARCH),x86_64)
  PKG_SOURCE:=$(PKG_NAME)+wolfssl@x86_64-linux-musl@x86_64@fast+lto
  PKG_HASH:=00cb71adac9a8874a68802502ab004c837f6c47936de2d5f58aeb03152583b11
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
