# SPDX-License-Identifier: MIT
#
# Copyright (C) 2026 qt <qingting1016@outlook.com>

include $(TOPDIR)/rules.mk

PKG_NAME:=jluNetworkLogin
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=qt <qingting1016@outlook.com>

include $(INCLUDE_DIR)/package.mk

define Package/jluNetworkLogin
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Campus Network
  TITLE:=JLU campus network login client (DrCOM)
  URL:=https://github.com/qingting04/jluNetworkLogin
  DEPENDS:=+libubus +libubox +libuci
endef

define Package/jluNetworkLogin/description
  Lightweight DrCOM client daemon for the JLU campus network.

  It performs the challenge/login/keepalive handshake, reconnects
  automatically when the session drops and exposes a "jlu-network-login"
  ubus object with "status" and "reconnect" methods used by the LuCI page.
endef

define Package/jluNetworkLogin/conffiles
/etc/config/jlu-network-login
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_CPPFLAGS) -std=c11 -D_GNU_SOURCE \
		-o $(PKG_BUILD_DIR)/jlu-network-login $(PKG_BUILD_DIR)/drcomd.c \
		$(TARGET_LDFLAGS) -lubus -lubox -luci
endef

define Package/jluNetworkLogin/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/jlu-network-login $(1)/usr/sbin/jlu-network-login
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/jlu-network-login.init $(1)/etc/init.d/jlu-network-login
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/jlu-network-login.config $(1)/etc/config/jlu-network-login
endef

$(eval $(call BuildPackage,jluNetworkLogin))
