# SPDX-Identifier-License: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=UnblockNeteaseMusic-Go
PKG_VERSION:=0.2.13
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/cnsilvan/UnblockNeteaseMusic/tar.gz/$(PKG_VERSION)?
PKG_HASH:=92201b7f04ab1015c806c672b98a29b97d0f137d9b60e6d35d279c2064ed86a4
PKG_BUILD_DIR:=$(BUILD_DIR)/UnblockNeteaseMusic-$(PKG_VERSION)

PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILE:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/cnsilvan/UnblockNeteaseMusic
GO_PKG_LDFLAGS_X:=$(GO_PKG)/version.Version=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/UnblockNeteaseMusic-Go
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=Revive Netease Cloud Music (Golang)
  URL:=https://github.com/cnsilvan/UnblockNeteaseMusic
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
endef

define Package/UnblockNeteaseMusic-Go/install
	$(call GoPackage/Package/Install/Bin,$(1))

	$(INSTALL_DIR) $(1)/usr/share/UnblockNeteaseMusicGo
	$(CP) ./files/* $(1)/usr/share/UnblockNeteaseMusicGo/
endef

$(eval $(call GoBinPackage,UnblockNeteaseMusic-Go))
$(eval $(call BuildPackage,UnblockNeteaseMusic-Go))
