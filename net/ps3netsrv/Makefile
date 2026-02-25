# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021-2026 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=ps3netsrv
PKG_VERSION:=20250803
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/jhonathanc/ps3netsrv/tar.gz/$(PKG_VERSION)?
PKG_HASH:=ea516ff938b93898cee44ececb30a428adf4387ad66fc7e584bc6f90e59f4cb4

PKG_LICENSE:=GPL-3.0-or-later
PKG_LICENSE_FILES:=LICENSE.TXT
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/ps3netsrv
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=File Transfer
  TITLE:=PS3 Game Server
  URL:=https://github.com/jhonathanc/ps3netsrv
  DEPENDS:=+libpthread +libstdcpp
endef

define Package/ps3netsrv/description
  ps3netsrv allows you to stream games and ISOs over the network to
  your CFW PlayStation(R) 3 system.
  This may be useful if you have a modified PS3, and your router
  has storage options.
endef

define Package/ps3netsrv/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ps3netsrv $(1)/usr/bin

	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/ps3netsrv.config $(1)/etc/config/ps3netsrv
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/ps3netsrv.init $(1)/etc/init.d/ps3netsrv
endef

$(eval $(call BuildPackage,ps3netsrv))
