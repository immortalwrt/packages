# Copyright (C) 2020 Lienol
#
# This is free software, licensed under the GNU General Public License v3.

include $(TOPDIR)/rules.mk

PKG_NAME:=trojan-go
PKG_VERSION:=0.10.6
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/p4gefau1t/trojan-go/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=925f02647dda944813f1eab0b71eac98b83eb5964ef5a6f63e89bc7eb4486c1f

PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/p4gefau1t/trojan-go
GO_PKG_BUILD_PKG:=$(GO_PKG)
GO_PKG_LDFLAGS_X:= \
	$(GO_PKG)/constant.Version=$(PKG_VERSION) \
	$(GO_PKG)/constant.Commit=v$(PKG_VERSION)
GO_PKG_TAGS:=full

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/trojan-go
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=An unidentifiable mechanism that helps you bypass GFW
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
  URL:=https://github.com/p4gefau1t/trojan-go
endef

$(eval $(call GoBinPackage,trojan-go))
$(eval $(call BuildPackage,trojan-go))
