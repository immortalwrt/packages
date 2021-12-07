# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=gg
PKG_VERSION:=0.1.9
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/mzz2017/gg/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=ddd8263d31729acc681b387e6a7b5c3e8a5981d148518fb03b77a14bc3978bbd

PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>
PKG_LICENSE:=AGPL-3.0-only
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/mzz2017/gg

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/gg
  SECTION:=net
  CATEGORY:=Network
  TITLE:=A command-line tool for one-click proxy
  URL:=https://github.com/mzz2017/gg
  DEPENDS:=@(arm||x86_64) +ca-bundle
endef

define Package/gg/description
  gg is a command-line tool for one-click proxy in your research and
  development.

  You can just add gg before another command to redirect its traffic
  to your proxy without installing v2ray or anything else.
  Usage example: gg python -m pip install torch.
endef

define Package/gg/conffiles
/root/.ggconfig.toml
endef

$(eval $(call GoBinPackage,gg))
$(eval $(call BuildPackage,gg))
