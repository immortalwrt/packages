# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2022 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=sing-box
PKG_VERSION:=1.1-beta13
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/SagerNet/sing-box/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=c4c4393685ab80b93eea2eb1d20bb960e2d98d7d0ffa8e0201eefde8fbb986e6

PKG_LICENSE:=GPL-3.0-or-later
PKG_LICENSE_FILE:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_CONFIG_DEPENDS:= \
	CONFIG_SING_BOX_BUILD_ACME \
	CONFIG_SING_BOX_BUILD_ECH \
	CONFIG_SING_BOX_BUILD_GRPC \
	CONFIG_SING_BOX_BUILD_GVISOR \
	CONFIG_SING_BOX_BUILD_QUIC \
	CONFIG_SING_BOX_BUILD_SHADOWSOCKSR \
	CONFIG_SING_BOX_BUILD_UTLS \
	CONFIG_SING_BOX_BUILD_WIREGUARD

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/sagernet/sing-box
GO_PKG_BUILD_PKG:=$(GO_PKG)/cmd/sing-box
GO_PKG_LDFLAGS_X:=$(GO_PKG)/constant.Version=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/sing-box
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=The universal proxy platform
  URL:=https://sing-box.sagernet.org/
  DEPENDS:=$(GO_ARCH_DEPENDS) \
    +ca-bundle \
    +kmod-inet-diag \
    +kmod-netlink-diag \
    +SING_BOX_BUILD_GVISOR:kmod-tun
endef

define Package/sing-box/config
  if PACKAGE_sing-box
    config SING_BOX_BUILD_ACME
    bool "Build with ACME TLS certificate issuer support"
    default n

    config SING_BOX_BUILD_ECH
    bool "Build with TLS ECH extension support"
    default y

    config SING_BOX_BUILD_GRPC
    bool "Build with standard gPRC support"
    default n
    help
      Standard gRPC has good compatibility but poor performance.

    config SING_BOX_BUILD_GVISOR
    bool "Build with gVisor support"
    default y

    config SING_BOX_BUILD_QUIC
    bool "Build with QUIC support"
    default y
    help
      Required by HTTP3 DNS transports, Naive inbound,
      Hysteria inbound / outbound, and v2ray QUIC transport.

    config SING_BOX_BUILD_SHADOWSOCKSR
    bool "Build with ShadowsockR support"
    default n

    config SING_BOX_BUILD_UTLS
    bool "Build with uTLS support"
    default n

    config SING_BOX_BUILD_WIREGUARD
    bool "Build with WireGuard support"
    default n
  endif
endef

PKG_BUILD_TAGS:=
ifneq ($(CONFIG_SING_BOX_BUILD_ACME),)
  PKG_BUILD_TAGS+=with_acme
endif
ifneq ($(CONFIG_SING_BOX_BUILD_ECH),)
  PKG_BUILD_TAGS+=with_ech
endif
ifneq ($(CONFIG_SING_BOX_BUILD_GRPC),)
  PKG_BUILD_TAGS+=with_grpc
endif
ifneq ($(CONFIG_SING_BOX_BUILD_GVISOR),)
  PKG_BUILD_TAGS+=with_gvisor
endif
ifneq ($(CONFIG_SING_BOX_BUILD_QUIC),)
  PKG_BUILD_TAGS+=with_quic
endif
ifneq ($(CONFIG_SING_BOX_BUILD_SHADOWSOCKSR),)
  PKG_BUILD_TAGS+=with_shadowsocksr
endif
ifneq ($(CONFIG_SING_BOX_BUILD_UTLS),)
  PKG_BUILD_TAGS+=with_utls
endif
ifneq ($(CONFIG_SING_BOX_BUILD_WIREGUARD),)
  PKG_BUILD_TAGS+=with_wireguard
endif
GO_PKG_TAGS:=$(subst $(space),$(comma),$(strip $(PKG_BUILD_TAGS)))

$(eval $(call GoBinPackage,sing-box))
$(eval $(call BuildPackage,sing-box))
