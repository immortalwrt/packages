# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=gallery-dl
PKG_VERSION:=1.21.1
PKG_RELEASE:=$(AUTORELEASE)

PYPI_NAME:=gallery_dl
PKG_HASH:=a0b56b60cec5f4914362040bfd78094bd2de51ec6a71296f9a4c32024d5ba686

PKG_LICENSE:=GPL-2.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

include ../../lang/python/pypi.mk
include $(INCLUDE_DIR)/package.mk
include ../../lang/python/python3-package.mk

define Package/gallery-dl
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=Command-line program to download image galleries and collections
  URL:=https://github.com/mikf/gallery-dl
  DEPENDS:= \
    +ca-certificates \
    +python3 \
    +python3-codecs \
    +python3-ctypes \
    +python3-email \
    +python3-requests \
    +python3-setuptools \
    +python3-xml
endef

define Package/gallery-dl/description
  gallery-dl is a command-line program to download image galleries
  and collections from several image hosting sites.

  It is a cross-platform tool with many configuration options and
  powerful filenaming capabilities.
endef

$(eval $(call Py3Package,gallery-dl))
$(eval $(call BuildPackage,gallery-dl))
$(eval $(call BuildPackage,gallery-dl-src))
