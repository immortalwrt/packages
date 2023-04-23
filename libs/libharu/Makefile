# SDPX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2021 Elon Huang <elonhhuang@gmail.com>

include $(TOPDIR)/rules.mk

PKG_NAME:=libharu
PKG_VERSION:=2.3.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/libharu/libharu/tar.gz/RELEASE_$(subst .,_,$(PKG_VERSION))?
PKG_HASH:=8f9e68cc5d5f7d53d1bc61a1ed876add1faf4f91070dbc360d8b259f46d9a4d2
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-RELEASE_$(subst .,_,$(PKG_VERSION))

PKG_MAINTAINER:=Elon Huang <elonhhuang@gmail.com>
PKG_LICENSE:=zlib
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_PARALLEL:=1
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libharu
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=free PDF library
  URL:=http://libharu.org/
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
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libhpdf.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libharu))
