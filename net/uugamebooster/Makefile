# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=uugamebooster
PKG_VERSION:=3.3.2
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(ARCH).tar.gz
PKG_SOURCE_URL:=https://uu.gdl.netease.com/uuplugin/openwrt-$(ARCH)/v$(PKG_VERSION)/uu.tar.gz?
ifeq ($(ARCH),aarch64)
  PKG_HASH:=d74e5daa7f6c40163849042d21fa6e71a4d21ea58c05e671699f9d090726adda
else ifeq ($(ARCH),arm)
  PKG_HASH:=2a13134cd37b149d89ec73cc8a4c3ea4f9853af7c7ccf5f390016e334eed60ae
else ifeq ($(ARCH),mipsel)
  PKG_HASH:=8d26267bce01a85dca43c91b9e71ab5ddc3447cb13789eaea233da7ed6f7d961
else ifeq ($(ARCH),x86_64)
  PKG_HASH:=02ba778fb59565213752de4383a7ad00301a091ecda4f9383337c222f7fb20fe
else
  PKG_HASH:=b9dd588617f9a839a84d19236d623a50a6b1b3850097b7d69bf3eafa32785979
endif

PKG_LICENSE:=Proprietary
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

include $(INCLUDE_DIR)/package.mk

STRIP:=true

TAR_CMD=$(HOST_TAR) -C $(1)/ $(TAR_OPTIONS)

define Package/uugamebooster
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=@(aarch64||arm||mipsel||x86_64) +kmod-tun
  TITLE:=NetEase UU Game Booster
  URL:=https://uu.163.com
endef

define Package/uugamebooster/description
  NetEase's UU Game Booster Accelerates Triple-A Gameplay and Market.
endef

define Build/Compile
endef

define Package/uugamebooster/conffiles
/usr/share/uugamebooster/.uuplugin_uuid
/usr/share/uugamebooster/uu.conf
endef

define Package/uugamebooster/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uuplugin $(1)/usr/bin/uugamebooster

	$(INSTALL_DIR) $(1)/usr/share/uugamebooster
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/uu.conf $(1)/usr/share/uugamebooster/uu.conf

	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/init.d
	$(INSTALL_CONF) ./files/uugamebooster.config $(1)/etc/config/uugamebooster
	$(INSTALL_BIN) ./files/uugamebooster.init $(1)/etc/init.d/uugamebooster

	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(CP) ./files/uugamebooster.uci $(1)/etc/uci-defaults/90-uugamebooster-cfg-migration
endef

$(eval $(call BuildPackage,uugamebooster))
