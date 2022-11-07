# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=lux
PKG_VERSION:=0.16.0
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/iawia002/lux/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=e16f3ec485793326c09f6b7096edacbb117fcbbd40341289e055ea19a5347033

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
