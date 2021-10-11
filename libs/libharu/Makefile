#
# Copyright (C) 2021 Elon Huang
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libharu
PKG_VERSION:=2.3.0
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/libharu/libharu/tar.gz/RELEASE_2_3_0?
PKG_HASH:=8f9e68cc5d5f7d53d1bc61a1ed876add1faf4f91070dbc360d8b259f46d9a4d2
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-RELEASE_2_3_0

PKG_MAINTAINER:= ElonH <elonhhuang@gmail.com>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
#PKG_CPE_ID:=cpe:/a:yaml-cpp_project:yaml-cpp

CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libharu
  SECTION:=development
  CATEGORY:=Libraries
  TITLE:=libhura
  URL:=https://github.com/libharu/libharu
  DEPENDS:=+libstdcpp +libpng
endef

define Package/libharu/description
  Haru is a free, cross platform, open-sourced software library for generating PDF.
  It supports the following features.

   1. Generating PDF files with lines, text, images.
   2. Outline, text annotation, link annotation.
   3. Compressing document with deflate-decode.
   4. Embedding PNG, Jpeg images.
   5. Embedding Type1 font and TrueType font.
   6. Creating encrypted PDF files.
   7. Using various character set (ISO8859-1~16, MSCP1250~8, KOI8-R).
   8. Supporting CJK fonts and encodings.

  You can add the feature of PDF creation by using Haru without understanding complicated internal structure of PDF.
endef


define Package/libharu/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libhpdf.soxxx $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libharu))
