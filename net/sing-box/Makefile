# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2022-2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=sing-box
PKG_VERSION:=1.14.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/SagerNet/sing-box/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=67dd8f8c37ecaaadcfcafad1f0827eed4b034c963b86fd3aa5c0d7a36876845d

PKG_LICENSE:=GPL-3.0-or-later
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>
PKG_CPE_ID:=cpe:/a:sagernet:sing-box

PKG_CONFIG_DEPENDS:= \
	CONFIG_SING_BOX_BUILD_NAIVE_OUTBOUND \
	CONFIG_SING_BOX_TINY_BUILD_ACME \
	CONFIG_SING_BOX_TINY_BUILD_CCM \
	CONFIG_SING_BOX_TINY_BUILD_CLASH_API \
	CONFIG_SING_BOX_TINY_BUILD_CLOUDFLARED \
	CONFIG_SING_BOX_TINY_BUILD_DHCP \
	CONFIG_SING_BOX_TINY_BUILD_EMBEDDED_TOR \
	CONFIG_SING_BOX_TINY_BUILD_GRPC \
	CONFIG_SING_BOX_TINY_BUILD_GVISOR \
	CONFIG_SING_BOX_TINY_BUILD_NAIVE_OUTBOUND \
	CONFIG_SING_BOX_TINY_BUILD_OCM \
	CONFIG_SING_BOX_TINY_BUILD_OPENCONNECT \
	CONFIG_SING_BOX_TINY_BUILD_OPENVPN \
	CONFIG_SING_BOX_TINY_BUILD_QUIC \
	CONFIG_SING_BOX_TINY_BUILD_TAILSCALE \
	CONFIG_SING_BOX_TINY_BUILD_USBIP \
	CONFIG_SING_BOX_TINY_BUILD_UTLS \
	CONFIG_SING_BOX_TINY_BUILD_V2RAY_API \
	CONFIG_SING_BOX_TINY_BUILD_WIREGUARD

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/sagernet/sing-box
GO_PKG_BUILD_PKG:=$(GO_PKG)/cmd/sing-box
GO_PKG_LDFLAGS:=-checklinkname=0
GO_PKG_LDFLAGS_X:= \
	$(GO_PKG)/constant.Version=$(PKG_VERSION) \
	runtime.godebugDefault=multipathtcp=0,tlssha1=1

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/sing-box/Default
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=The universal proxy platform
  URL:=https://sing-box.sagernet.org/
  DEPENDS:=+ca-bundle +kmod-inet-diag
  USERID:=sing-box=5566:sing-box=5566
endef

define Package/sing-box
  $(call Package/sing-box/Default)
  TITLE+= (full version)
  DEPENDS+= +kmod-netlink-diag +kmod-tun +SING_BOX_BUILD_NAIVE_OUTBOUND:libcronet
  CONFLICTS:=sing-box-tiny
  VARIANT:=full
  DEFAULT_VARIANT:=1
endef

define Package/sing-box/description
  Sing-box is a universal proxy platform which supports hysteria, SOCKS, Shadowsocks,
  ShadowTLS, Tor, trojan, VLess, VMess, WireGuard and so on.
endef

define Package/sing-box/config
  depends on $(subst @,,$(GO_ARCH_DEPENDS))

  config SING_BOX_BUILD_NAIVE_OUTBOUND
  def_bool y
  depends on !(arc||armeb||loongarch64||mips||mips64||powerpc||TARGET_gemini)
endef

define Package/sing-box-tiny
  $(call Package/sing-box/Default)
  TITLE+= (tiny/custom version)
  DEPENDS+= +SING_BOX_TINY_BUILD_NAIVE_OUTBOUND:libcronet
  PROVIDES:=sing-box
  VARIANT:=tiny
endef

Package/sing-box-tiny/description:=$(Package/sing-box/description)

define Package/sing-box-tiny/config
  depends on $(subst @,,$(GO_ARCH_DEPENDS))

  config SING_BOX_TINY_BUILD_ACME
  bool "Build with ACME TLS certificate issuer support"

  config SING_BOX_TINY_BUILD_CCM
  bool "Build with Claude Code Multiplexer service support"

  config SING_BOX_TINY_BUILD_CLASH_API
  bool "Build with Clash API support"
  default y

  config SING_BOX_TINY_BUILD_CLOUDFLARED
  bool "Build with Cloudflare Tunnel inbound support"

  config SING_BOX_TINY_BUILD_DHCP
  bool "Build with DHCP support"

  config SING_BOX_TINY_BUILD_EMBEDDED_TOR
  bool "Build with embedded Tor support"
  depends on BROKEN

  config SING_BOX_TINY_BUILD_GRPC
  bool "Build with standard gPRC support"
  help
    Standard gRPC has good compatibility but poor performance.

  config SING_BOX_TINY_BUILD_GVISOR
  bool "Build with gVisor support"
  default y if aarch64||arm||i386||x86_64

  config SING_BOX_TINY_BUILD_NAIVE_OUTBOUND
  bool "Build with NaiveProxy outbound support"
  depends on !(arc||armeb||loongarch64||mips||mips64||powerpc||TARGET_gemini)

  config SING_BOX_TINY_BUILD_OCM
  bool "Build with OpenAI Codex Multiplexer service support"

  config SING_BOX_TINY_BUILD_OPENCONNECT
  bool "Build with OpenConnect support"

  config SING_BOX_TINY_BUILD_OPENVPN
  bool "Build with OpenVPN support"

  config SING_BOX_TINY_BUILD_QUIC
  bool "Build with QUIC support"
  default y
  help
    Required by HTTP3 DNS transports, Naive inbound,
    Hysteria inbound / outbound, and v2ray QUIC transport.

  config SING_BOX_TINY_BUILD_TAILSCALE
  bool "Build with Tailscale support"

  config SING_BOX_TINY_BUILD_USBIP
  bool "Build with USB/IP support"

  config SING_BOX_TINY_BUILD_UTLS
  bool "Build with uTLS support"
  default y

  config SING_BOX_TINY_BUILD_V2RAY_API
  bool "Build with V2Ray API support"

  config SING_BOX_TINY_BUILD_WIREGUARD
  bool "Build with WireGuard support"
  default y if aarch64||arm||i386||x86_64
endef

ifeq ($(BUILD_VARIANT),full)
  GO_PKG_TAGS:=$(subst $(space),$(comma),$(strip \
	badlinkname \
	tfogo_checklinkname0 \
	with_acme \
	with_clash_api \
	with_cloudflared \
	with_dhcp \
	with_gvisor \
	$(if $(CONFIG_SING_BOX_BUILD_NAIVE_OUTBOUND),with_naive_outbound) \
	with_openconnect \
	with_openvpn \
	with_quic \
	with_tailscale \
	with_usbip \
	with_utls \
	with_wireguard \
  ))
else
  GO_PKG_TAGS:=$(subst $(space),$(comma),$(strip \
	badlinkname \
	tfogo_checklinkname0 \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_ACME),with_acme) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_CCM),with_ccm) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_CLASH_API),with_clash_api) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_CLOUDFLARED),with_cloudflared) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_DHCP),with_dhcp) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_EMBEDDED_TOR),with_embedded_tor) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_GRPC),with_grpc) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_GVISOR),with_gvisor) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_NAIVE_OUTBOUND),with_naive_outbound) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_OCM),with_ocm) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_OPENCONNECT),with_openconnect) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_OPENVPN),with_openvpn) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_QUIC),with_quic) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_TAILSCALE),with_tailscale) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_USBIP),with_usbip) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_UTLS),with_utls) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_V2RAY_API),with_v2ray_api) \
	$(if $(CONFIG_SING_BOX_TINY_BUILD_WIREGUARD),with_wireguard) \
  ))
endif

ifneq ($(findstring with_naive_outbound,$(GO_PKG_TAGS)),)
  TARGET_LDFLAGS += -lcronet
endif

define Package/sing-box/conffiles
/etc/config/sing-box
/etc/sing-box/
endef

Package/sing-box-tiny/conffiles=$(Package/sing-box/conffiles)

define Package/sing-box/install
	$(call GoPackage/Package/Install/Bin,$(1))

	$(INSTALL_DIR) $(1)/etc/sing-box
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/release/config/config.json $(1)/etc/sing-box

	$(INSTALL_DIR) $(1)/etc/config/
	$(INSTALL_CONF) ./files/sing-box.conf $(1)/etc/config/sing-box
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) ./files/sing-box.init $(1)/etc/init.d/sing-box
endef

Package/sing-box-tiny/install=$(Package/sing-box/install)

$(eval $(call BuildPackage,sing-box))
$(eval $(call BuildPackage,sing-box-tiny))
