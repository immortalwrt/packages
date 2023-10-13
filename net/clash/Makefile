# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=clash
PKG_VERSION:=1.18.0
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/Dreamacro/clash/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=139794f50d3d94f438bab31a993cf25d7cbdf8ca8e034f3071e0dd0014069692

PKG_LICENSE:=GPL-3.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/Dreamacro/clash
GO_PKG_LDFLAGS_X:=$(GO_PKG)/constant.Version=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/clash
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=A rule-based tunnel in Go
  URL:=https://github.com/Dreamacro/clash
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
endef

define Package/clash/description
  Clash is a cross-platform rule-based proxy utility that runs on the
  network and application layer, supporting various proxy and
  anti-censorship protocols out-of-the-box.

  It has been adopted widely by the Internet users in some countries
  and regions where the Internet is heavily censored or blocked.
  Either way, Clash can be used by anyone who wants to improve their
  Internet experience.
endef

$(eval $(call GoBinPackage,clash))
$(eval $(call BuildPackage,clash))
