# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=speedtest-go
PKG_VERSION:=1.1.4
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/showwin/speedtest-go/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=381b483369fe7ced347b750af6a721b7dedd2da6efceef10396b89683213cf04

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/showwin/speedtest-go

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/speedtest-go
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Test Internet Speed
  URL:=https://github.com/showwin/speedtest-go
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
endef

define Package/speedtest-go/description
  Command Line Interface and pure Go API to
  Test Internet Speed using speedtest.net
endef

$(eval $(call GoBinPackage,speedtest-go))
$(eval $(call BuildPackage,speedtest-go))
