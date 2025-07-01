include $(TOPDIR)/rules.mk

PKG_NAME:=fan2go
PKG_VERSION:=0.11.1
PKG_RELEASE:=1
PKG_LICENSE:=AGPL-3.0
PKG_LICENSE_FILES:=LICENSE
PKG_REV:=e605d47c249361b39b183ccf5411beff5c1450c5


PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/markusressel/$(PKG_NAME)/tar.gz/$(PKG_VERSION)?
PKG_HASH:=02baca96ed1be6824e9bf6ca33198f94cc9319af44e04677a7f9c55c60abb319

PKG_MAINTAINER:=Dee.H.Y <dongfengweixiao@hotmail.com>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/markusressel/fan2go/

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

CGO_CPPFLAGS="${CPPFLAGS}"
CGO_CXXFLAGS="${CXXFLAGS}"
GO_PKG_LDFLAGS_X:=$(GO_PKG)/cmd/global.Version=$(PKG_VERSION) \
                  $(GO_PKG)/cmd/global.Commit=$(PKG_REV) \
                  $(GO_PKG)/cmd/global.Date=$(PKG_BUILD_TIME)
GO_PKG_TAGS:=netgo,disable_nvml

define Package/fan2go
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=dynamic fan speed control
  URL:=https://github.com/markusressel/fan2go
  DEPENDS:=$(GO_ARCH_DEPENDS) +libsensors
endef

define Package/fan2go/description
  A simple daemon providing dynamic fan speed control based on temperature sensors. 
endef

$(eval $(call GoBinPackage,fan2go))
$(eval $(call BuildPackage,fan2go))
