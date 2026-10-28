include $(TOPDIR)/rules.mk

PKG_NAME:=geoview
PKG_VERSION:=0.2.9
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/snowie2000/geoview/tar.gz/$(PKG_VERSION)?
PKG_HASH:=b080a141505a3180c3b81468304864e4373c4868680ff39fb82ee6973e3b5e94

PKG_LICENSE:=Apache-2.0
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=snowie2000

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/snowie2000/geoview

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/geoview
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=IP Addresses and Names
  TITLE:=A geofile toolkit
  URL:=https://github.com/snowie2000/geoview
  DEPENDS:=$(GO_ARCH_DEPENDS)
endef

define Package/geoview/description
  geoview is a handy tool to extract useful information from geo* files.
endef

$(eval $(call GoBinPackage,geoview))
$(eval $(call BuildPackage,geoview))
