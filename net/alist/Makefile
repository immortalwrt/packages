# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=alist
PKG_VERSION:=3.19.0
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/alist-org/alist/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=77080f88dc789253c46efaf7adc141a9d7250d477653db7270941b35d14f82ab

PKG_LICENSE:=AGPL-3.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

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

define Package/alist/conffiles
/etc/alist/
/etc/config/alist
endef

WEB_VERSION:=$(PKG_VERSION)
WEB_FILE:=$(PKG_NAME)-web-$(WEB_VERSION).tar.gz
define Download/alist-web
	URL:=https://github.com/alist-org/alist-web/releases/download/$(WEB_VERSION)/
	URL_FILE:=dist.tar.gz
	FILE:=$(WEB_FILE)
	HASH:=5f8d00dc2b805e69630e5f00878bd45571f19250675738348fef274a2d9e8d9d
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

	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) $(CURDIR)/files/alist.config $(1)/etc/config/alist
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(CURDIR)/files/alist.init $(1)/etc/init.d/alist
endef

$(eval $(call Download,alist-web))
$(eval $(call GoBinPackage,alist))
$(eval $(call BuildPackage,alist))
