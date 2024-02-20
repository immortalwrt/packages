# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2022 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=btop
PKG_VERSION:=1.3.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL=https://codeload.github.com/aristocratos/btop/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=331d18488b1dc7f06cfa12cff909230816a24c57790ba3e8224b117e3f0ae03e

PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>
PKG_LICENSE:=Apache-2.0
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_FLAGS:=no-lto
CMAKE_BINARY_SUBDIR:=openwrt-build

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/btop
  SECTION:=admin
  CATEGORY:=Administration
  TITLE:=A monitor of resources
  URL:=https://github.com/aristocratos/btop
  DEPENDS:=+libstdcpp
endef

define Package/btop/description
  Resource monitor that shows usage and stats for processor, memory,
  disks, network and processes.

  C++ version and continuation of bashtop and bpytop.
endef

CMAKE_OPTIONS+= -DBTOP_GPU=OFF -DBTOP_LTO=OFF

define Package/btop/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/btop $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/share
	$(CP) $(PKG_INSTALL_DIR)/usr/share/btop $(1)/usr/share/

	$(INSTALL_DIR) $(1)/etc/profile.d
	$(CP) $(CURDIR)/files/btop.sh $(1)/etc/profile.d/
endef

$(eval $(call BuildPackage,btop))
