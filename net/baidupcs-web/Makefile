# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2022 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=baidupcs-web
PKG_VERSION:=3.7.4-nnew
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/zxlhhyccc/BaiduPCS-Go.git
PKG_SOURCE_VERSION:=ee2d75bacc1453b088a0cb9aed58e29026ceec92
PKG_MIRROR_HASH:=771a3459f9e9c982c1b5808f71addf9313d9075afe988e9fdf3cd53dd27e9ee0

PKG_LICENSE:=Apache-2.0
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DEPENDS:=golang/host go-rice/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/zxlhhyccc/BaiduPCS-Go
GO_PKG_LDFLAGS_X:=main.Version=v$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/baidupcs-web
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Download Manager
  TITLE:=A web controller for BaiduPCS-Go
  URL:=https://github.com/zxlhhyccc/BaiduPCS-Go
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
endef

define Build/Compile
	( \
		pushd "$(PKG_BUILD_DIR)/internal/pcsweb" ; \
		rice embed-go ; \
		popd ; \
		$(call GoPackage/Build/Compile) ; \
	)
endef

define Package/baidupcs-web/install
	$(call GoPackage/Package/Install/Bin,$(PKG_INSTALL_DIR))

	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(GO_PKG_BUILD_BIN_DIR)/BaiduPCS-Go $(1)/usr/bin/baidupcs-web
endef

$(eval $(call GoBinPackage,baidupcs-web))
$(eval $(call BuildPackage,baidupcs-web))
