# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2020-2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=ykdl
PKG_VERSION:=1.8.0a2
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/SeaHOH/ykdl/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=b5ad62f83ceb191784a369d28bce4f11bd724c227fa584abfed4d01323824574

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
