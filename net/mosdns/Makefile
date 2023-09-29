# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=mosdns
PKG_VERSION:=5.2.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/IrineSistiana/mosdns/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=f6ed7c29408f4db69f8b5b9fa041e77b2460e561fc889116edb8f6021fad966a

PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/IrineSistiana/mosdns
GO_PKG_LDFLAGS_X:=main.version=v$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/mosdns
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=IP Addresses and Names
  TITLE:=A plug-in DNS forwarder/splitter
  URL:=https://github.com/IrineSistiana/mosdns
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
  PROVIDES:=mosdns-neo
endef

GO_PKG_TARGET_VARS:=$(filter-out CGO_ENABLED=%,$(GO_PKG_TARGET_VARS)) CGO_ENABLED=0

define Package/mosdns/install
	$(call GoPackage/Package/Install/Bin,$(1))

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scripts/openwrt/mosdns-init-openwrt $(1)/etc/init.d/mosdns

	$(INSTALL_DIR) $(1)/etc/mosdns
	$(INSTALL_DATA) ./files/config.yaml $(1)/etc/mosdns/config.yaml
endef

define Package/mosdns/postinst
#!/bin/sh

# check if we are on real system
if [ -z "$${IPKG_INSTROOT}" ]; then
	/etc/init.d/mosdns stop >/dev/null 2>&1
	/etc/init.d/mosdns disable >/dev/null 2>&1
fi
exit 0
endef

$(eval $(call GoBinPackage,mosdns))
$(eval $(call BuildPackage,mosdns))
