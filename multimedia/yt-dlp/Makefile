# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=yt-dlp
PKG_VERSION:=2022.3.8.2
PKG_RELEASE:=$(AUTORELEASE)

PYPI_NAME:=yt-dlp
PKG_HASH:=68546578c18e6ce87450b53769d5d5b7f5a23e5209784976db6c7ccbf7954b21

PKG_LICENSE:=Unlicense
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrtorg>

include ../../lang/python/pypi.mk
include $(INCLUDE_DIR)/package.mk
include ../../lang/python/python3-package.mk

define Package/yt-dlp
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=A youtube-dl fork with additional features and fixes
  URL:=https://github.com/yt-dlp/yt-dlp
  DEPENDS:= \
    +ca-certificates \
    +python3 \
    +python3-codecs \
    +python3-ctypes \
    +python3-email \
    +python3-mutagen \
    +python3-cryptodomex \
    +python3-setuptools \
    +python3-websockets \
    +python3-xml
endef

define Package/yt-dlp/description
  yt-dlp is a youtube-dl fork based on the now inactive youtube-dlc.
  The main focus of this project is adding new features and patches
  while also keeping up to date with the original project.
endef

$(eval $(call Py3Package,yt-dlp))
$(eval $(call BuildPackage,yt-dlp))
$(eval $(call BuildPackage,yt-dlp-src))
