# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=speedtest-go
PKG_VERSION:=1.1.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/showwin/speedtest-go/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=381b483369fe7ced347b750af6a721b7dedd2da6efceef10396b89683213cf04

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

PKG_CONFIG_DEPENDS:= \
	CONFIG_SPEEDTEST_GO_COMPRESS_GOPROXY \
	CONFIG_SPEEDTEST_GO_COMPRESS_UPX

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/showwin/speedtest-go
GO_PKG_LDFLAGS:=-s -w

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/speedtest-go/config
config SPEEDTEST_GO_COMPRESS_GOPROXY
	bool "Compiling with GOPROXY proxy"
	default n

config SPEEDTEST_GO_COMPRESS_UPX
	bool "Compress executable files with UPX"
	depends on !mips64
	default n
endef

ifeq ($(CONFIG_SPEEDTEST_GO_COMPRESS_GOPROXY),y)
	export GO111MODULE=on
	export GOPROXY=https://goproxy.baidu.com
endif

define Package/speedtest-go
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Test Internet Speed
  URL:=https://github.com/showwin/speedtest-go
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
endef

define Package/speedtest-go/description
  Command Line Interface and pure Go API to
  Test Internet Speed using speedtest.net
endef

define Build/Compile
	$(call GoPackage/Build/Compile)
ifeq ($(CONFIG_SPEEDTEST_GO_COMPRESS_UPX),y)
	$(STAGING_DIR_HOST)/bin/upx --lzma --best $(GO_PKG_BUILD_BIN_DIR)/speedtest-go
endif
endef

$(eval $(call GoBinPackage,speedtest-go))
$(eval $(call BuildPackage,speedtest-go))
