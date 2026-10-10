#
# Copyright (C) 2022 Krypton Lee <jun.k.lee199410@outlook.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qt6tools
PKG_BASE:=6.12
PKG_BUGFIX:=0
PKG_VERSION:=$(PKG_BASE).$(PKG_BUGFIX)
PKG_RELEASE:=1

PKG_SOURCE:=qttools-everywhere-src-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://mirrors.tencent.com/qt/archive/qt/$(PKG_BASE)/$(PKG_VERSION)/submodules/ \
		  https://mirrors.aliyun.com/qt/archive/qt/$(PKG_BASE)/$(PKG_VERSION)/submodules/ \
		  http://download.qt-project.org/archive/qt/$(PKG_BASE)/$(PKG_VERSION)/submodules/
PKG_HASH:=8dab8f3611496486a470ad5f115ceea584f36bc22a2b8b6f6ebdbafbb8160693
HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/qttools-everywhere-src-$(PKG_VERSION)

PKG_MAINTAINER:=Krypton Lee <jun.k.lee199410@outlook.com>
PKG_LICENSE:=LGPL-2.1
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:qt:qt

HOST_BUILD_DEPENDS:=qt6base/host libxml2/host
HOST_BUILD_PARALLEL:=1
PKG_HOST_ONLY:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/qt6tools
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Qt6
  TITLE:=Qt6 Tools
  URL:=http://qt-project.org
  BUILDONLY:=1
  HIDDEN:=1
endef

CMAKE_HOST_OPTIONS+= \
	-DFEATURE_assistant=OFF \
	-DFEATURE_clang=OFF \
	-DFEATURE_designer=OFF \
	-DFEATURE_distancefieldgenerator=OFF \
	-DFEATURE_kmap2qmap=OFF \
	-DFEATURE_pixeltool=OFF \
	-DFEATURE_qdbus=OFF \
	-DFEATURE_qev=OFF \
	-DFEATURE_qtattributionsscanner=OFF \
	-DFEATURE_qtdiag=OFF \
	-DFEATURE_qdoc=OFF \
	-DFEATURE_qtplugininfo=OFF

$(eval $(call BuildPackage,qt6tools))
$(eval $(call HostBuild))
