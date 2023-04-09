#
# Copyright (C) 2007-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=wxbase
PKG_VERSION:=3.2.2.1
PKG_RELEASE:=1

PKG_SOURCE:=wxWidgets-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://github.com/wxWidgets/wxWidgets/releases/download/v$(PKG_VERSION)
PKG_HASH:=dffcb6be71296fff4b7f8840eb1b510178f57aa2eb236b20da41182009242c02

PKG_BUILD_DIR:=$(BUILD_DIR)/wxWidgets-$(PKG_VERSION)
PKG_CHECK_FORMAT_SECURITY:=0
PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libwxbase
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Cross-platform C++ framework
  URL:=http://www.wxwidgets.org/
  DEPENDS:=+libexpat +libstdcpp +zlib +libpthread +libcurl
endef

define Package/libwxbase/description
  wxBase contains most of the non-GUI classes from the wxWindows cross-
  -platform C++ framework. There are 2 categories: generally useful portable
  code (date/time handling, command line parsing, regular expression support)
  and wrappers for the OS objects (files, directories, sockets, threads,
  etc.) allowing you to write portable programs easily.
endef

TARGET_CFLAGS += $(FPIC)

CONFIGURE_ARGS+= \
	--enable-shared \
	--disable-rpath \
	--disable-gui \
	--disable-monolithic \
	--enable-plugins \
	--disable-universal \
	--disable-nanox \
	--disable-gpe \
	--enable-optimise \
	--disable-debug \
	--disable-stl \
	--disable-debug_flag \
	--disable-mediactrl \
	--disable-debug_info \
	--disable-debug_gdb \
	--disable-debug_cntxt \
	--disable-mem_tracing \
	--disable-profile \
	--disable-no_rtti \
	--disable-no_exceptions \
	--disable-compat28 \
	--disable-compat30 \
	--enable-intl \
	--enable-ipv6 \
	--disable-backtrace \
	--enable-exceptions \
	--disable-sound \
	--enable-largefile \
	\
	--without-gtk \
	--without-motif \
	--without-mac \
	--without-msw \
	--without-cocoa \
	--without-wine \
	--without-x11 \
	--without-libpng \
	--without-libjpeg \
	--without-libtiff \
	--without-libjbig \
	--without-libxpm \
	--without-libmspack \
	--without-sdl \
	--without-opengl \
	--without-dmalloc \
	--with-regex="sys" \
	--with-zlib="sys" \
	--with-expat="sys" \
	--without-gtk-prefix \
	--without-x \
	--without-libiconv-prefix \
	--without-sdl-prefix \
	--disable-precomp-headers

CONFIGURE_ARGS := $(filter-out --disable-nls, $(CONFIGURE_ARGS))

UNICODE=yes

ifeq ($(UNICODE),yes)
  CONFIGURE_ARGS+= --enable-unicode
  LIB_PFX:=u
else
  CONFIGURE_ARGS+= --disable-unicode
  LIB_PFX:=
endif

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/wx-config $(1)/usr/bin/
	$(SED) "s,$(PKG_BUILD_DIR),$(STAGING_DIR)/usr,g" $(1)/usr/bin/wx-config
	$(SED) 's,-I$$$${includedir}/wx-3.2,-I$(STAGING_DIR)/usr/include/wx-3.2,g' $(1)/usr/bin/wx-config
	$(SED) 's,-I$$$${libdir}/wx/include,-I$(STAGING_DIR)/usr/lib/wx/include,g' $(1)/usr/bin/wx-config

	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/wx-3.2 $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libwx_*.so* $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/wx $(1)/usr/lib/
endef

define Package/libwxbase/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libwx_*.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libwxbase))
