# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=gotop
PKG_VERSION:=4.1.4
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/xxxserxxx/gotop/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=9fe5eb25ee253e5679cd0dede0ec6e075d6782442bc3007bb9fea8c44e66b857

PKG_LICENSE:=MIT
PKG_LICENSE_FILE:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/xxxserxxx/gotop
GO_PKG_LDFLAGS_X:=main.Version=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/gotop
  SECTION:=admin
  CATEGORY:=Administration
  TITLE:=A terminal based graphical activity monitor
  URL:=https://github.com/xxxserxxx/gotop
  DEPENDS:=$(GO_ARCH_DEPENDS)
endef

define Package/gotop/description
  Another terminal based graphical activity monitor.
endef

$(eval $(call GoBinPackage,gotop))
$(eval $(call BuildPackage,gotop))
