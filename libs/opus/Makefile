#
# Copyright (C) 2014-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=opus
PKG_VERSION:=1.5.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://downloads.xiph.org/releases/opus
PKG_HASH:=b84610959b8d417b611aa12a22565e0a3732097c6389d19098d844543e340f85

PKG_MAINTAINER:=Ted Hess <thess@kitchensync.net>, Ian Leonard <antonlacon@gmail.com>
PKG_LICENSE:=BSD-3-Clause
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:opus-codec:opus

PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

define Package/libopus
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=OPUS Audio Codec
  URL:=https://opus-codec.org
endef

define Package/libopus/description
 Opus is a totally open, royalty-free, highly versatile audio codec. Opus is
 unmatched for interactive speech and music transmission over the Internet, but
 is also intended for storage and streaming applications.
endef

MESON_ARGS+= \
	-Ddocs=disabled \
	-Dextra-programs=disabled

ifeq ($(CONFIG_SOFT_FLOAT),y)
	MESON_ARGS+= \
		-Dfixed-point=true
endif

ifneq ($(findstring neon,$(CONFIG_CPU_TYPE))$(findstring aarch64,$(CONFIG_ARCH)),)
	MESON_ARGS+= \
		-Dfixed-point=true
endif

CPU_ASM_BLACKLIST:=xscale arm926ej-s
ifneq ($(findstring $(call qstrip,$(CONFIG_CPU_TYPE)),$(CPU_ASM_BLACKLIST)),)
	MESON_ARGS+= -Dasm=disabled
endif

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/opus $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libopus.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/opus.pc $(1)/usr/lib/pkgconfig/
endef

define Package/libopus/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libopus.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libopus))
