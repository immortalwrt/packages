# SPDX-License-Identifier: MIT
#
# Copyright (C) 2026 hakurei kyaru

include $(TOPDIR)/rules.mk

PKG_NAME:=ztewifi
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/hakureiyuyuko/ztewifi/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=a57ca1d9d35e68a7464f34a840c5666a696238f438b1ded409e4c5dcd9090ee1

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

PKG_MAINTAINER:=hakurei kyaru <admin@yuyuko.moe>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/hakureiyuyuko/ztewifi
GO_PKG_BUILD_PKG:=github.com/hakureiyuyuko/ztewifi

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/ztewifi
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Status tool for ZTE portable WiFi hotspots
  URL:=https://github.com/hakureiyuyuko/ztewifi
  DEPENDS:=$(GO_ARCH_DEPENDS)
endef

define Package/ztewifi/description
  Command line tool that reads signal, network and device information from a
  ZTE portable WiFi hotspot (RedCap Mobile Hotspot, e.g. MU3650 / F40) through
  the device's built-in web API, and can toggle the wireless radio of the
  hotspot itself.

  It is the backend of the luci-app-ztewifi LuCI application.
endef

$(eval $(call GoBinPackage,ztewifi))
$(eval $(call BuildPackage,ztewifi))
