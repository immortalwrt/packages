# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=lux
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/iawia002/lux.git
PKG_SOURCE_DATE:=2022-01-19
PKG_SOURCE_VERSION:=bfc1b1d4c11c7eb28aa169d924d621e868622527
PKG_MIRROR_HASH:=a635fd4e5e35c8f3a2a0e53f595445699b90060c7deef57d9e46befa56876e30
PKG_VERSION:=0.12.0-$(call version_abbrev,$(PKG_SOURCE_VERSION))

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
