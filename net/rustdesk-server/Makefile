# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=rustdesk-server
PKG_VERSION:=1.1.12
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/rustdesk/rustdesk-server/tar.gz/$(PKG_VERSION)?
PKG_HASH:=48c85d9032043d644cee12ccbf4025ea4dc2f4c271fb3f73d836d8e1c67083a0

PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>
PKG_LICENSE:=AGPL-3.0-only
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DEPENDS:=rust/host
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include ../../lang/rust/rust-package.mk

define Package/rustdesk-server
  SECTION:=net
  CATEGORY:=Network
  TITLE:=RustDesk Server Program
  DEPENDS:=@(aarch64||arm||x86_64) @(!arm||TARGET_bcm53xx||HAS_FPU)
  URL:=https://rustdesk.com/server
endef

define Package/rustdesk-server/description
  Self-host your own RustDesk server, it is free and open source.
endef

define Package/rustdesk-server/conffiles
/etc/config/rustdesk
/etc/rustdesk
endef

define Package/rustdesk-server/install
	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/bin/{hbbr,hbbs} $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/init.d/
	$(INSTALL_BIN) ./files/rustdesk.conf $(1)/etc/config/rustdesk
	$(INSTALL_BIN) ./files/rustdesk.init $(1)/etc/init.d/rustdesk
endef

$(eval $(call RustBinPackage,rustdesk-server))
$(eval $(call BuildPackage,rustdesk-server))
