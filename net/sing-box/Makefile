# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2022 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=sing-box
PKG_VERSION:=1.1-beta6
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/SagerNet/sing-box/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=6cadde3259f79401327bb9fafa4aa6d50a73d1d9680dbc126beea932e2c3be73

PKG_LICENSE:=GPL-3.0-or-later
PKG_LICENSE_FILE:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_CONFIG_DEPENDS:= \
	CONFIG_SING_BOX_BUILD_ACME \
	CONFIG_SING_BOX_BUILD_ECH \
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
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle +SING_BOX_BUILD_GVISOR:kmod-tun
endef

define Package/sing-box/config
  if PACKAGE_sing-box
    config SING_BOX_BUILD_ACME
    bool "Build with ACME TLS certificate issuer support"
    default n

    config SING_BOX_BUILD_ECH
    bool "Build with TLS ECH extension support"
    default y

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

ifneq ($(CONFIG_SING_BOX_BUILD_ACME),)
  GO_PKG_TAGS+=with_acme
endif
ifneq ($(CONFIG_SING_BOX_BUILD_ECH),)
  GO_PKG_TAGS+=with_ech
endif
ifneq ($(CONFIG_SING_BOX_BUILD_GVISOR),)
  GO_PKG_TAGS+=gvisor
endif
ifneq ($(CONFIG_SING_BOX_BUILD_QUIC),)
  GO_PKG_TAGS+=with_quic
endif
ifneq ($(CONFIG_SING_BOX_BUILD_SHADOWSOCKSR),)
  GO_PKG_TAGS+=with_shadowsocksr
endif
ifneq ($(CONFIG_SING_BOX_BUILD_UTLS),)
  GO_PKG_TAGS+=with_utls
endif
ifneq ($(CONFIG_SING_BOX_BUILD_WIREGUARD),)
  GO_PKG_TAGS+=with_wireguard
endif
GO_PKG_TAGS:=$(subst $(space),$(comma),$(strip $(GO_PKG_TAGS)))

$(eval $(call GoBinPackage,sing-box))
$(eval $(call BuildPackage,sing-box))
