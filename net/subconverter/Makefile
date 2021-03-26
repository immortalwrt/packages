# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=subconverter
PKG_VERSION:=0.6.4
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tindy2013/subconverter.git
PKG_SOURCE_DATE:=2021-03-25
PKG_SOURCE_VERSION:=3afe9986bea32abb3b2a3415bf3018ecb01a5bb4
PKG_MIRROR_HASH:=5128a1967a7c548a577038f4a64efd8b1c4022c6ad19ccfa8073efbb5e370250

PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=jpcre2 libcron quickjspp rapidjson
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/subconverter
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Utility to convert between various subscription format
  URL:=https://github.com/tindy2013/subconverter
  DEPENDS:=+libpthread +libstdcpp +libevent2 +libyaml-cpp +libpcre2 +libcurl +zlib
endef

define Package/subconverter/description
  Utility to convert between various proxy subscription formats.
endef

TARGET_CXXFLAGS := $(FPIC) $(filter-out -O%,$(TARGET_CXXFLAGS)) -O3
TARGET_CXXFLAGS += -Wall -Wextra -ffunction-sections -fdata-sections -flto
TARGET_LDFLAGS += -Wl,--gc-sections -flto

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

define Package/subconverter/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/subconverter $(1)/usr/bin/subconverter
	$(INSTALL_DIR) $(1)/etc/subconverter
	$(CP) $(PKG_BUILD_DIR)/base/* $(1)/etc/subconverter/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/subconverter.init $(1)/etc/init.d/subconverter
endef

$(eval $(call BuildPackage,subconverter))
