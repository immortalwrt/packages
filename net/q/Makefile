include $(TOPDIR)/rules.mk

PKG_NAME:=q
PKG_VERSION:=0.19.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/natesales/q/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=9ce80c34ba2b75fc9ea486df412e7bdf9d9dceffa1a08f4113d0ab3210757a92

PKG_LICENSE:=GPL-3.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Milinda Brantini <C_A_T_T_E_R_Y@outlook.com>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/natesales/q
GO_PKG_LDFLAGS_X:= main.version=$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/q
  SECTION:=net
  CATEGORY:=Network
  TITLE:=A tiny command line DNS client.
  URL:=https://github.com/natesales/q
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
endef

define Package/q/description
  A tiny command line DNS client with support for UDP, TCP, DoT, DoH, DoQ and ODoH.
endef

$(eval $(call GoBinPackage,q))
$(eval $(call BuildPackage,q))
