#
# Copyright (C) 2016-2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=yaaw
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2020-08-03
PKG_SOURCE_URL:=https://github.com/binux/yaaw.git
PKG_SOURCE_VERSION:=7511684b9af552445d0dd849ac25705b79a5ad0d
PKG_MIRROR_HASH:=4aecc3d025b5c73ce28d18e36939caf3c4577473b90b03923aaae3da0a342f7b

PKG_LICENSE:=LGPL-3.0
PKG_MAINTAINER:=Hsing-Wang Liao <kuoruan@gmail.com>

include $(INCLUDE_DIR)/package.mk

define Package/yaaw
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Download Manager
  TITLE:=Yet another aria2 web frontend
  URL:=https://github.com/binux/yaaw
  DEPENDS:=+aria2
  PKGARCH:=all
endef

define Package/yaaw/description
	Yet Another Aria2 Web Frontend in pure HTML/CSS/Javascirpt.
endef

define Build/Compile
endef

define Package/yaaw/install
	$(INSTALL_DIR) $(1)/www/yaaw
	$(CP) \
		$(PKG_BUILD_DIR)/{css,img,js} \
		$(PKG_BUILD_DIR)/{index.html,offline.appcache} \
		$(1)/www/yaaw
endef

$(eval $(call BuildPackage,yaaw))
