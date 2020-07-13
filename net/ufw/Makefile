#
# Copyright (C) 2020 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ufw
PKG_VERSION:=0.36
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://launchpad.net/ufw/$(PKG_VERSION)/$(PKG_VERSION)/+download/
PKG_HASH:=754b22ae5edff0273460ac9f57509c3938187e0cf4fb9692c6a02833fff33cfc
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

PKG_MAINTAINER:=[CTCGFW]Project OpenWrt / CN_SZTL <cnsztl@project-openwrt.eu.org>
PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk
include ../../lang/python/python3-package.mk

PYTHON3_PKG_SETUP_ARGS:=

define Package/$(PKG_NAME)
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Firewall
  TITLE:=Ufw stands for Uncomplicated Firewall
  URL:=https://launchpad.net/ufw
  DEPENDS:= \
    +iptables \
    +python3 \
    +python3-setuptools
endef

define Package/$(PKG_NAME)/description
  Ufw stands for Uncomplicated Firewall, and is program for managing a netfilter firewall.
  It provides a command line interface and aims to be uncomplicated and easy to use.
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_INSTALL_DIR)/* $(1)/
endef

$(eval $(call Py3Package,$(PKG_NAME)))
$(eval $(call BuildPackage,$(PKG_NAME)))
$(eval $(call BuildPackage,$(PKG_NAME)-src))
