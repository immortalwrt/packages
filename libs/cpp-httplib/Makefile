# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (C) 2020 ElonH <elonhhuang@gmail.com>

include $(TOPDIR)/rules.mk

PKG_NAME:=cpp-httplib
PKG_VERSION:=0.16.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/yhirose/cpp-httplib/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=c125022eb85eaa12235518dc4638be93b62c3216d0f87b655af7b17b71b38851

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=ElonH <elonhhuang@gmail.com>

CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/cpp-httplib
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=A C++11 single-file header-only cross platform HTTP/HTTPS library.
  URL:=https://github.com/yhirose/cpp-httplib
  BUILDONLY:=1
endef

define Package/cpp-httplib/description
  A C++11 single-file header-only cross platform HTTP/HTTPS library.
  It's extremely easy to setup. Just include `httplib.h` file in your code!
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,cpp-httplib))
