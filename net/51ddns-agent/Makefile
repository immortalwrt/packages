# SPDX-License-Identifier: GPL-2.0-only
# Copyright (C) 2026 51DDNS

include $(TOPDIR)/rules.mk

PKG_NAME:=51ddns-agent
PKG_VERSION:=0.6.1
PKG_RELEASE:=1

PKG_SOURCE:=51ddns-openwrt-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/21hkcloud/51ddns-openwrt/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=59e8c4f6606ec2403fb4f144f555766f79c16a7f078847c1da4e9ed5d8886951
PKG_BUILD_DIR:=$(BUILD_DIR)/51ddns-openwrt-$(PKG_VERSION)

PKG_MAINTAINER:=51DDNS <support@51ddns.com>
PKG_LICENSE:=Apache-2.0
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/21hkcloud/51ddns-openwrt
GO_PKG_BUILD_PKG:=$(GO_PKG)/cmd/51ddns-agent
GO_PKG_LDFLAGS_X:=main.agentVersion=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/51ddns-agent
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=VPN
  TITLE:=51DDNS remote access agent
  URL:=https://www.51ddns.com/
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle +frpc
endef

define Package/51ddns-agent/description
  Securely connects an OpenWrt device to the self-hosted 51DDNS control plane.
endef

define Package/51ddns-agent/conffiles
/etc/config/51ddns
endef

define Package/51ddns-agent/postinst
#!/bin/sh
[ -n "$${IPKG_INSTROOT}" ] && exit 0
/etc/init.d/51ddns-agent enable >/dev/null 2>&1 || true
/etc/init.d/51ddns-agent restart >/dev/null 2>&1 || true
exit 0
endef

define Package/51ddns-agent/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(GO_PKG_BUILD_BIN_DIR)/51ddns-agent $(1)/usr/bin/51ddns-agent
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/51ddns.config $(1)/etc/config/51ddns
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/51ddns-agent.init $(1)/etc/init.d/51ddns-agent
	$(INSTALL_DIR) $(1)/usr/libexec
	$(INSTALL_BIN) ./files/51ddns-agent-start $(1)/usr/libexec/51ddns-agent-start
	$(INSTALL_DIR) $(1)/etc/51ddns $(1)/var/lib/51ddns
endef

$(eval $(call BuildPackage,51ddns-agent))
