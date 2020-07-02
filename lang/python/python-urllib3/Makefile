#
# Copyright (C) 2007-2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=python-urllib3
PKG_VERSION:=1.25.9
PKG_RELEASE:=1

PKG_MAINTAINER:=Josef Schlehofer <pepe.schlehofer@gmail.com>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE.txt
PKG_CPE_ID:=cpe:/a:urllib3_project:urllib3

PYPI_NAME:=urllib3
PKG_HASH:=3018294ebefce6572a474f0604c2021e33b3fd8006ecd11d62107a5d2a963527

include ../pypi.mk
include $(INCLUDE_DIR)/package.mk
include ../python-package.mk
include ../python3-package.mk

define Package/python-urllib3/Default
  SUBMENU:=Python
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Sanity-friendly HTTP client
  URL:=https://urllib3.readthedocs.io/
endef

define Package/python-urllib3
$(call Package/python-urllib3/Default)
  DEPENDS:=+PACKAGE_python-urllib3:python
  VARIANT:=python
endef

define Package/python-urllib3/description
  HTTP library with thread-safe connection pooling, file post, and more.
endef

define Package/python3-urllib3
$(call Package/python-urllib3/Default)
  DEPENDS:=+PACKAGE_python3-urllib3:python3
  VARIANT:=python3
endef

define Package/python3-urllib3/description
$(call Package/python-urllib3/description)
.
(Variant for Python3)
endef

$(eval $(call PyPackage,python-urllib3))
$(eval $(call BuildPackage,python-urllib3))
$(eval $(call BuildPackage,python-urllib3-src))

$(eval $(call Py3Package,python3-urllib3))
$(eval $(call BuildPackage,python3-urllib3))
$(eval $(call BuildPackage,python3-urllib3-src))
