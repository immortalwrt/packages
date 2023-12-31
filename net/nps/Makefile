# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=nps
PKG_VERSION:=0.26.10
PKG_RELEASE:=4

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/ehang-io/nps/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=1b2fe9d251f55105d65027a1cee464f65d2f6ab3bd4a20e4655e5135db68aee7

PKG_LICENSE:=Apache-2.0
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINTER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=ehang.io/nps
GO_PKG_BUILD_PKG:=$(GO_PKG)/cmd/...

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define nps/templates
  define Package/$(1)
    SECTION:=net
    CATEGORY:=Network
    SUBMENU:=Web Servers/Proxies
    TITLE:=A intranet penetration proxy server ($(1))
    DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
    URL:=https://ehang-io.github.io/nps
  endef

  define Package/$(1)/description
  NPS is a lightweight, high-performance, powerful intranet penetration proxy server,
  with a powerful web management terminal.

  This package contains the $(1).
  endef

  define Package/$(1)/install
	$$(call GoPackage/Package/Install/Bin,$$(PKG_INSTALL_DIR))

	$$(INSTALL_DIR) $$(1)/usr/bin
	$$(INSTALL_BIN) $$(PKG_INSTALL_DIR)/usr/bin/$(1) $$(1)/usr/bin/
  endef
endef

define Build/UpdateDependencies
	cd $(PKG_BUILD_DIR) && \
		go mod tidy
endef

NPS_COMPONENTS:=npc nps

define Build/Compile
	$(call Build/UpdateDependencies)
	$(call GoPackage/Build/Compile)
endef

$(foreach component,$(NPS_COMPONENTS), \
  $(eval $(call nps/templates,$(component))) \
  $(eval $(call GoBinPackage,$(component))) \
  $(eval $(call BuildPackage,$(component))) \
)
