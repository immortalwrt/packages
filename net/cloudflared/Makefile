# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=cloudflared
PKG_VERSION:=2022.1.0
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/cloudflare/cloudflared/tar.gz/$(PKG_VERSION)?
PKG_HASH:=a2edfa8eacae1875de36936b4a3228bdc4b6b65f34dc07daec35cdc1b25715b2

PKG_LICENSE:=Proprietary
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_CONFIG_DEPENDS:= \
	CONFIG_CLOUDFLARED_COMPRESS_GOPROXY \
	CONFIG_CLOUDFLARED_COMPRESS_UPX

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/cloudflare/cloudflared
GO_PKG_LDFLAGS:=-s -w
GO_PKG_LDFLAGS_X:=main.Version=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/cloudflared/config
config CLOUDFLARED_COMPRESS_GOPROXY
	bool "Compiling with GOPROXY proxy"
	default n

config CLOUDFLARED_COMPRESS_UPX
	bool "Compress executable files with UPX"
	depends on !mips64
	default n
endef

ifeq ($(CONFIG_CLOUDFLARED_COMPRESS_GOPROXY),y)
	export GO111MODULE=on
	export GOPROXY=https://goproxy.bj.bcebos.com
endif

define Package/cloudflared
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Argo Tunnel client
  URL:=https://developers.cloudflare.com/argo-tunnel/
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
endef

define Package/cloudflared/description
  Contains the command-line client for Argo Tunnel, a tunneling daemon
  that proxies any local webserver through the Cloudflare network.
  Extensive documentation can be found in the Argo Tunnel section of
  the Cloudflare Docs.
endef

define Build/Compile
	$(call GoPackage/Build/Compile)
ifeq ($(CONFIG_CLOUDFLARED_COMPRESS_UPX),y)
	$(STAGING_DIR_HOST)/bin/upx --lzma --best $(GO_PKG_BUILD_BIN_DIR)/cloudflared
endif
endef

$(eval $(call GoBinPackage,cloudflared))
$(eval $(call BuildPackage,cloudflared))
