# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=go-nats
PKG_VERSION:=0.0.1
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/enobufs/go-nats.git
PKG_SOURCE_DATE:=2019-09-23
PKG_SOURCE_VERSION:=4effc32e0f4006da0636b24f4468cf32ce494d71
PKG_MIRROR_HASH:=3f99471f9ab1967bb1236981bfdd23d97fc7e73b4ea52e0ee625e81301c63beb

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/enobufs/go-nats

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/go-nats
  SECTION:=net
  CATEGORY:=Network
  TITLE:=A NAT type discovery tool
  URL:=https://github.com/enobufs/go-nats
  DEPENDS:=$(GO_ARCH_DEPENDS)
endef

define Package/go-nats/description
  A NAT type discovery tool using STUN.
endef

$(eval $(call GoBinPackage,go-nats))
$(eval $(call BuildPackage,go-nats))
