# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2020-2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=ykdl
PKG_VERSION:=1.8.1
PKG_RELEASE:=$(AUTORELEASE)

PYPI_NAME:=ykdl
PKG_HASH:=28b6415c03efd6141034c8d46c0483d27276bcd7d189fd12e48dd5762f79a868

PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE.txt

include ../../lang/python/pypi.mk
include $(INCLUDE_DIR)/package.mk
include ../../lang/python/python3-package.mk

define Package/ykdl
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=a video downloader focus on China mainland video sites
  URL:=https://github.com/SeaHOH/ykdl
  DEPENDS:= \
    +ca-certificates \
    +ffmpeg \
    +python3 \
    +python3-email \
    +python3-xml \
    +python3-codecs \
    +python3-ctypes \
    +python3-setuptools
endef

$(eval $(call Py3Package,ykdl))
$(eval $(call BuildPackage,ykdl))
$(eval $(call BuildPackage,ykdl-src))
