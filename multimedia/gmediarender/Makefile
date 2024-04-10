# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021-2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=gmediarender
PKG_RELEASE=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/hzeller/gmrender-resurrect.git
PKG_SOURCE_DATE:=2023-07-16
PKG_SOURCE_VERSION:=3a1234f8694c0f406717c34f700cb07324d29076
PKG_MIRROR_HASH:=9c23874f005647abaf3133882a21fd102ee41d7094256420672c2b6815bc7abc

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/gmediarender
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=Resource efficient UPnP/DLNA renderer
  DEPENDS:=+glib2 +gstreamer1 +gstreamer1-utils +gst1-plugins-base \
    +gst1-plugins-bad +gst1-plugins-good +libupnp
endef

define Package/gmediarender/description
  gmediarender implements the server component that provides UPnP
  controllers a means to render media content (audio, video and images)
  from a UPnP media server.
endef

define Package/gmediarender/config
	select PACKAGE_gstreamer1-plugins-bad
	select PACKAGE_gstreamer1-plugins-good
endef

define Package/gmediarender/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/gmediarender $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/share/gmediarender
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/gmediarender/grender-*.png $(1)/usr/share/gmediarender/
endef

$(eval $(call BuildPackage,gmediarender))
