include $(TOPDIR)/rules.mk

PKG_NAME:=nexttrace
PKG_VERSION:=1.1.7-1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/sjlleo/nexttrace-core/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=1c937a9f7c2f1d4a3e71e63db2929a5b24d438c63efd9715b00277f1b3add4cb
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-core-$(PKG_VERSION)

PKG_LICENSE:=GPL-3.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Bradford Zhang <zyc@zyc.name>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/xgadget-lab/nexttrace
GO_PKG_LDFLAGS_X:=$(GO_PKG)/config.Version=v$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/nexttrace
  SECTION:=net
  CATEGORY:=Network
  TITLE:=An open source visual route tracking CLI tool
  URL:=https://github.com/sjlleo/nexttrace-core
  DEPENDS:=$(GO_ARCH_DEPENDS)
endef

define Package/nexttrace/description
  An open source visual route tracking CLI tool
endef

$(eval $(call GoBinPackage,nexttrace))
$(eval $(call BuildPackage,nexttrace))
