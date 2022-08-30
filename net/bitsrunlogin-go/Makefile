#
# Copyright (C) 2021 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=BitSrunLoginGo
PKG_VERSION:=3.2
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/Mmx233/BitSrunLoginGo/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=5b5c8db5869be4ccadb81938b86c33362e170f119145d0fe3493f03f53a7eedd

PKG_LICENSE:=AGPL-3.0
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/Mmx233/BitSrunLoginGo

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/BitSrunLoginGo
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Campus Network
  TITLE:=Bit Srun auto login tool
  URL:=https://github.com/Mmx233/BitSrunLoginGo
  DEPENDS:=$(GO_ARCH_DEPENDS)
endef

$(eval $(call GoBinPackage,BitSrunLoginGo))
$(eval $(call BuildPackage,BitSrunLoginGo))
