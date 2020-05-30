#
# Copyright (C) 2019 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=gmrender-resurrect
PKG_VERSION:=0.0.8
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/hzeller/gmrender-resurrect.git
PKG_SOURCE_VERSION:=26d8f7edf5336bc30f7334c6ad459bf7f4f90ff2
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz

PKG_LICENSE:=GPLv3
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=CN_SZTL <cnsztl@project-openwrt.eu.org>

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

PKG_INSTALL:=1
PKG_FIXUP:=autoreconf
PKG_USE_MIPS16:=0
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	CATEGORY:=Multimedia
	SECTION:=multimedia
	URL:=https://github.com/hzeller/gmrender-resurrect
	TITLE:=Resource efficient UPnP/DLNA renderer, optimal for Raspberry Pi, CuBox or a general MediaServer.
	DEPENDS:=+libgstreamer1 +gstreamer1-plugins-bad +gstreamer1-plugins-base +gstreamer1-plugins-good +gstreamer1-plugins-ugly +gst1-libav +gst1-mod-alsa +libupnp
endef

define Package/$(PKG_NAME)/description
	Resource efficient UPnP/DLNA renderer, optimal for Raspberry Pi, CuBox or a general MediaServer.
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/gmediarender $(1)/usr/bin/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
