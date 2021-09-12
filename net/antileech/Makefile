#
# Copyright (C) 2021 ImmortalWrt
# <https://immortalwrt.org>
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=antileech
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2019-10-09
PKG_SOURCE_URL:=https://github.com/persmule/amule-dlp.antiLeech.git
PKG_SOURCE_VERSION:=f5ce55d2fc0026c28e30cfc8cab4fb45ad1e0161
PKG_MIRROR_HASH:=a3458f4b1e6934ffd98d65030ce904df6e6d4854d224d584d13d8efcd34a0001

PKG_FIXUP:=autoreconf
PKG_BUILD_DEPENDS:=libgd
PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/antileech
  SUBMENU:=P2P
  SECTION:=net
  CATEGORY:=Network
  TITLE:=AntiLeech for aMule
  URL:=https://github.com/persmule/amule-dlp.antiLeech
  DEPENDS:=+amule +libc +libwxbase
endef

define Package/antileech/description
  Dynamic Leech Protection(DLP) is a part of eMule Xtreme Mod at first.
  This project aim to make DLP available for aMule. This repo contains
  the plugin library "libantiLeech".
endef

define Build/Configure
	$(SED) "s:^AC_CHECK_PROG.WXCONFIG,.*::g" $(PKG_BUILD_DIR)/configure.ac
	$(SED) "s:wx-config --cppflags:$(STAGING_DIR)/usr/bin/wx-config --cppflags:g" $(PKG_BUILD_DIR)/configure.ac

	cd $(PKG_BUILD_DIR); $(SHELL) ./autogen.sh
	$(call Build/Configure/Default)
endef

MAKE_FLAGS += HOSTCC="$(HOSTCC)"

define Package/antileech/install
	$(INSTALL_DIR) $(1)/usr/share/amule
	$(CP) $(PKG_INSTALL_DIR)/usr/share/amule/libantiLeech.so* $(1)/usr/share/amule/
endef

$(eval $(call BuildPackage,antileech))
