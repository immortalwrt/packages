# SPDX-License-Identifier: MIT
#
# Copyright (C) 2026 qt <qingting1016@outlook.com>

include $(TOPDIR)/rules.mk

PKG_NAME:=hustNetworkLogin
PKG_VERSION:=0.2.0
PKG_RELEASE:=1

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=qt <qingting1016@outlook.com>

include $(INCLUDE_DIR)/package.mk

define Package/hustNetworkLogin
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Campus Network
  TITLE:=HUST campus network auto login (Srun ePortal)
  URL:=https://github.com/qingting04/hustNetworkLogin
  DEPENDS:=+libcurl +libopenssl +libubus +libubox
endef

define Package/hustNetworkLogin/description
  Automatic login daemon for the HUST (Srun ePortal) campus network.

  It probes the connection every 15 seconds, logs in again when the portal
  intercepts traffic and exposes a "hust-network-login" ubus object with
  "status" and "reconnect" methods that the LuCI page uses.
endef

define Package/hustNetworkLogin/conffiles
/etc/config/hust-network-login
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_CPPFLAGS) -pthread \
		-o $(PKG_BUILD_DIR)/hust-network-login $(PKG_BUILD_DIR)/main.c \
		$(TARGET_LDFLAGS) -lcurl -lcrypto -lubus -lubox -pthread
endef

define Package/hustNetworkLogin/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/hust-network-login $(1)/usr/bin/hust-network-login
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/hust-network-login.init $(1)/etc/init.d/hust-network-login
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/hust-network-login.config $(1)/etc/config/hust-network-login
endef

$(eval $(call BuildPackage,hustNetworkLogin))
