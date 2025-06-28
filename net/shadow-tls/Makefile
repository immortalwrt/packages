# SPDX-License-Identifier: GPL-3.0-only
include $(TOPDIR)/rules.mk

PKG_NAME:=shadow-tls
PKG_VERSION:=0.2.25
PKG_RELEASE:=1
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/ihciah/shadow-tls.git
PKG_SOURCE_VERSION:=dee3a5a819d6f56cfdd56c44a0d42be186c44238
PKG_MIRROR_HASH:=skip

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:= SakuraFallingMad

PKG_BUILD_DIR:=$(BUILD_DIR)/shadow-tls-$(PKG_VERSION)

PKG_BUILD_DEPENDS:=rust/host
PKG_USE_MIPS16:=0
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include ../../lang/rust/rust-package.mk

define Package/shadow-tls
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=Shadow-TLS: A proxy to evade censorship
  URL:=https://github.com/ihciah/shadow-tls
  DEPENDS:=+libopenssl
endef

define Package/shadow-tls/description
  Shadow-TLS is a proxy to evade DPI and censorship, designed to mimic TLS traffic.
endef

define Build/Compile
	CARGO_TARGET_$(call UPPERCASE,$(RUSTC_TARGET_NAME))_LINKER="$(TARGET_CC)" \
		cargo build --release --target $(RUSTC_TARGET_NAME) --features tokio-runtime
endef

define Package/shadow-tls/install
	$(INSTALL_DIR) $(1)/usr/bin
	$$(INSTALL_BIN) $$(PKG_INSTALL_DIR)/bin/$(1) $$(1)/usr/bin/
endef

$(eval $(call BuildPackage,shadow-tls))
