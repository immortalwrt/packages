#
# Copyright (C) 2021 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=BitSrunLoginGo
PKG_VERSION:=2.6
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/Mmx233/BitSrunLoginGo/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=fe18f741c71e64b14e167e5c7abeed53efc3c9c3ee5b8414a8a05b7cfa45eac5

PKG_LICENSE:=AGPL-3.0
PKG_LICENSE_FILES:=LICENSE

PKG_CONFIG_DEPENDS:= \
	CONFIG_BITSRUNLOGIN_GO_COMPRESS_GOPROXY \
	CONFIG_BITSRUNLOGIN_GO_COMPRESS_UPX

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/Mmx233/BitSrunLoginGo
GO_PKG_LDFLAGS:=-s -w

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/BitSrunLoginGo/config
config BITSRUNLOGIN_GO_COMPRESS_GOPROXY
	bool "Compiling with GOPROXY proxy"
	default n

config BITSRUNLOGIN_GO_COMPRESS_UPX
	bool "Compress executable files with UPX"
	depends on !mips64
	default n
endef

ifeq ($(CONFIG_BITSRUNLOGIN_GO_COMPRESS_GOPROXY),y)
	export GO111MODULE=on
	export GOPROXY=https://goproxy.bj.bcebos.com
endif

define Package/BitSrunLoginGo
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Campus Network
  TITLE:=Bit Srun auto login tool
  URL:=https://github.com/Mmx233/BitSrunLoginGo
  DEPENDS:=$(GO_ARCH_DEPENDS)
endef

define Build/Compile
	$(call GoPackage/Build/Compile)
ifeq ($(CONFIG_BITSRUNLOGIN_GO_COMPRESS_UPX),y)
	$(STAGING_DIR_HOST)/bin/upx --lzma --best $(GO_PKG_BUILD_BIN_DIR)/BitSrunLoginGo
endif
endef

$(eval $(call GoBinPackage,BitSrunLoginGo))
$(eval $(call BuildPackage,BitSrunLoginGo))
