# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=subconverter
PKG_BASE_VERSION:=0.7.1
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tindy2013/subconverter.git
PKG_SOURCE_DATE:=2021-10-01
PKG_SOURCE_VERSION:=94696a5da52e1efbdd03b7862c6b8e378958ac7b
PKG_MIRROR_HASH:=39d638035c0556c658209a7a9afe4f947714f6707e155a9561c606d0cd028539

PKG_VERSION:=$(PKG_BASE_VERSION)-$(PKG_SOURCE_DATE)-$(call version_abbrev,$(PKG_SOURCE_VERSION))

PKG_LICENSE:=GPL-3.0
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=jpcre2 libcron quickjspp rapidjson toml11
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/subconverter
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Utility to convert between various subscription format
  URL:=https://github.com/tindy2013/subconverter
  DEPENDS:=+libatomic +libcurl +libevent2 +libpcre2 +libpthread \
	+libstdcpp +libyaml-cpp +zlib
endef

define Package/subconverter/description
  Utility to convert between various proxy subscription formats.
endef

TARGET_CXXFLAGS := $(FPIC) $(filter-out -O%,$(TARGET_CXXFLAGS)) -O3
TARGET_CXXFLAGS += -Wall -Wextra -ffunction-sections -fdata-sections -flto
TARGET_LDFLAGS += -Wl,--gc-sections -flto

CMAKE_OPTIONS += \
	 -DCMAKE_BUILD_TYPE=Release \
	 -DCMAKE_EXE_LINKER_FLAGS="-latomic"

define Package/subconverter/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/subconverter $(1)/usr/bin/subconverter
	$(INSTALL_DIR) $(1)/etc/subconverter
	$(CP) $(PKG_BUILD_DIR)/base/* $(1)/etc/subconverter/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/subconverter.init $(1)/etc/init.d/subconverter
endef

$(eval $(call BuildPackage,subconverter))
