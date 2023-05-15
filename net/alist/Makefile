# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=alist
PKG_VERSION:=3.17.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/alist-org/alist/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=70647bcec0d7856692b33e5d77c072df821e1f61f88512c569ef5b545a53adfa

PKG_LICENSE:=AGPL-3.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/alist-org/alist/v3
GO_PKG_LDFLAGS_X:= \
	$(GO_PKG)/internal/conf.Version=$(PKG_VERSION) \
	$(GO_PKG)/internal/conf.WebVersion=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/alist
  SECTION:=net
  CATEGORY:=Network
  TITLE:=A file list program that supports multiple storage
  URL:=https://alist.nn.ci
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle +fuse-utils
endef

WEB_VERSION:=$(PKG_VERSION)
WEB_FILE:=$(PKG_NAME)-web-$(WEB_VERSION).tar.gz
define Download/alist-web
	URL:=https://github.com/alist-org/alist-web/releases/download/$(WEB_VERSION)/dist.tar.gz?
	URL_FILE:=$(WEB_FILE)
	FILE:=$(WEB_FILE)
	HASH:=85718110e958b9543fd99d14f1acea0d95042bedccbe1569177e8e9995a48aaf
endef

define Build/Prepare
	$(call Build/Prepare/Default)

	( \
		mkdir -p $(PKG_BUILD_DIR)/public ; \
		gzip -dc $(DL_DIR)/$(WEB_FILE) | $(HOST_TAR) -C $(PKG_BUILD_DIR)/public $(TAR_OPTIONS) ; \
	)
endef

define Package/alist/install
	$(call GoPackage/Package/Install/Bin,$(PKG_INSTALL_DIR))

	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/alist $(1)/usr/bin/
endef

$(eval $(call Download,alist-web))
$(eval $(call GoBinPackage,alist))
$(eval $(call BuildPackage,alist))
