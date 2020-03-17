#
# Copyright (C) 2007-2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=django-restframework39
PKG_VERSION:=3.9.4
PKG_RELEASE:=1

PKG_SOURCE:=djangorestframework-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://files.pythonhosted.org/packages/source/d/djangorestframework
PKG_HASH:=50b781f6cbeb98f673aa76ed8e572a019a45e52bdd4ad09001072dfd91ab07c8
PKG_BUILD_DIR:=$(BUILD_DIR)/djangorestframework-$(PKG_VERSION)

PKG_MAINTAINER:=Alexandru Ardelean <ardeleanalex@gmail.com>
PKG_LICENSE:=BSD-3-Clause
PKG_LICENSE_FILES:=LICENSE.md

include $(INCLUDE_DIR)/package.mk
include ../python-package.mk
include ../python3-package.mk

define Package/django-restframework39/Default
  SUBMENU:=Python
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Web APIs for Django, made easy.
  URL:=https://www.django-rest-framework.org
endef

define Package/python-django-restframework39
$(call Package/django-restframework39/Default)
  DEPENDS:= \
	+PACKAGE_python-django-restframework39:python \
	python-django1
  VARIANT:=python
  MDEPENDS:=python-django1
endef

define Package/python-django-restframework39/description
  Web APIs for Django, made easy. (3.9 series)
endef

define Package/python3-django-restframework39
$(call Package/django-restframework39/Default)
  DEPENDS:= \
	+PACKAGE_python3-django-restframework39:python3 \
	+PACKAGE_python3-django-restframework39:python3-django1
  CONFLICTS:=python3-django-restframework
  VARIANT:=python3
endef

define Package/python3-django-restframework39/description
$(call Package/python-django-restframework39/description)
.
(Variant for Python3)
endef

$(eval $(call PyPackage,python-django-restframework39))
$(eval $(call BuildPackage,python-django-restframework39))
$(eval $(call BuildPackage,python-django-restframework39-src))

$(eval $(call Py3Package,python3-django-restframework39))
$(eval $(call BuildPackage,python3-django-restframework39))
$(eval $(call BuildPackage,python3-django-restframework39-src))
