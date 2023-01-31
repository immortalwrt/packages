# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=webdav-go
PKG_VERSION:=4.1.1
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/hacdias/webdav/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=de968329b0429b7f2c312d69706762b210240a813e0b939009e9480c7c09d86d
PKG_BUILD_DIR:=$(BUILD_DIR)/webdav-$(PKG_VERSION)

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=ElonH <elonhhuang@gmail.com>

PKG_BUILD_DEPENDS:=golang/host
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

GO_PKG:=github.com/hacdias/webdav

include $(INCLUDE_DIR)/package.mk
include ../../lang/golang/golang-package.mk

define Package/webdav-go
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=File Transfer
  TITLE:=Simple Go WebDAV server
  URL:=https://github.com/hacdias/webdav
  DEPENDS:=$(GO_ARCH_DEPENDS)
endef

define Package/webdav-go/description
  WebDAV command line interface is really easy to use so you can easily
  create a WebDAV server for your own user. By default, it runs on a
  random free port and supports JSON, YAML and TOML configuration.
endef

define Package/webdav-go/install
	$(call GoPackage/Package/Install/Bin,$(PKG_INSTALL_DIR))

	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/webdav $(1)/usr/bin/webdav-go
endef

$(eval $(call GoBinPackage,webdav-go))
$(eval $(call BuildPackage,webdav-go))
