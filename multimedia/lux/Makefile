# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=lux
PKG_VERSION:=0.14.0
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/iawia002/lux/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=3d485c9703851f3fb5cdee9b029b5b6855f84bfd29b44cae310a031a6fa8c00f

PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/iawia002/lux
GO_PKG_BUILD_PKG:=$$(GO_PKG)
GO_PKG_LDFLAGS:=-s -w

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/lux
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=A fast, simple and clean video downloader
  URL:=https://github.com/iawia002/lux
  DEPENDS:=$(GO_ARCH_DEPENDS) +ffmpeg
endef

$(eval $(call GoBinPackage,lux))
$(eval $(call BuildPackage,lux))
