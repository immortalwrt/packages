include $(TOPDIR)/rules.mk

PKG_NAME:=nexttrace
PKG_VERSION:=1.5.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/nxtrace/NTrace-core/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=6def8e05d0311aa864e6faf99884ae408fa4c2705232671c334224fa0e34cd3b
PKG_BUILD_DIR:=$(BUILD_DIR)/NTrace-core-$(PKG_VERSION)

PKG_LICENSE:=GPL-3.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Bradford Zhang <zyc@zyc.name>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

GO_PKG:=github.com/nxtrace/NTrace-core
GO_PKG_BUILD_PKG:=$(GO_PKG)
GO_PKG_LDFLAGS:=-checklinkname=0
GO_PKG_LDFLAGS_X:=$(GO_PKG)/config.Version=v$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/nexttrace
  SECTION:=net
  CATEGORY:=Network
  TITLE:=An open source visual route tracking CLI tool
  URL:=https://github.com/nxtrace/NTrace-core
  DEPENDS:=$(GO_ARCH_DEPENDS) +ca-bundle
endef

define Package/nexttrace/description
  An open source visual route tracking CLI tool
endef

POW_NAME:=powclient
POW_VERSION:=0.2.0
POW_SOURCE:=$(POW_NAME)-$(POW_VERSION).tar.gz
POW_SOURCE_URL:=https://codeload.github.com/tsosunchia/powclient/tar.gz/v$(POW_VERSION)?
POW_HASH:=055413707533fd44d0967bc2ad74df6e6aea0f202354ec9f91b3123b5d3f2d70

define Download/powclient
  FILE:=$(POW_SOURCE)
  URL:=$(POW_SOURCE_URL)
  HASH:=$(POW_HASH)
endef
$(eval $(call Download,powclient))

define Build/Prepare
	$(call Build/Prepare/Default)
	mkdir -p $(PKG_BUILD_DIR)/$(POW_NAME)-src
	tar -xzf $(DL_DIR)/$(POW_SOURCE) -C $(PKG_BUILD_DIR)/$(POW_NAME)-src --strip-components=1
	find $(PKG_BUILD_DIR)/$(POW_NAME)-src -name "go.mod" -exec sed -i 's/^go 1\..*/go 1.23/' {} +
endef

define Package/nexttrace/install
	$(call GoPackage/Package/Install/Bin,$(PKG_INSTALL_DIR))
	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/NTrace-core $(1)/usr/bin/nexttrace
endef

$(eval $(call GoBinPackage,nexttrace))
$(eval $(call BuildPackage,nexttrace))
