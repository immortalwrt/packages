#
# Copyright (C) 2021 Zxilly <zhouxinyu1001@gmail.com>
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ua2f
PKG_VERSION:=3.7
PKG_RELEASE:=10

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Zxilly/UA2F.git
PKG_SOURCE_VERSION:=bae547dc58ac4a5b22c165e037ce9a9ab0b90dd8
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
PKG_MIRROR_HASH:=82dc44954cfc87d9288ba8a2214cf044a1ad36c1625252cdc37d0d2b91157010

PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILE:=LICENSE

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/ua2f
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  TITLE:=Change User-Agent to Fwords
  URL:=https://github.com/Zxilly/UA2F
  DEPENDS:=+iptables-mod-nfqueue +libipset \
	+libnetfilter-conntrack +libnetfilter-queue
endef

define Package/ua2f/description
  Change User-agent to Fwords to prevent being checked by Dr.Com.
endef

define Package/ua2f/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ua2f $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/init/ua2f $(1)/etc/init.d/ua2f
endef

$(eval $(call BuildPackage,ua2f))
