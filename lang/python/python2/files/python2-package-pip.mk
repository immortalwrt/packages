#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Package/python2-pip
$(call Package/python2/Default)
  TITLE:=Python $(PYTHON2_VERSION) pip module
  VERSION:=$(PYTHON2_PIP_VERSION)-$(PYTHON2_PIP_PKG_RELEASE)
  LICENSE:=MIT
  LICENSE_FILES:=LICENSE.txt
#  CPE_ID:=cpe:/a:python:pip # not currently handled this way by uscan
  DEPENDS:=+python2 +python2-setuptools +python-pip-conf
endef

define Py2Package/python2-pip/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/usr/lib/python$(PYTHON2_VERSION)/site-packages
	$(CP) $(PKG_BUILD_DIR)/install-pip/usr/bin/pip$(PYTHON2_VERSION) $(1)/usr/bin
	$(LN) pip$(PYTHON2_VERSION) $(1)/usr/bin/pip2
	$(CP) \
		$(PKG_BUILD_DIR)/install-pip/usr/lib/python$(PYTHON2_VERSION)/site-packages/pip \
		$(PKG_BUILD_DIR)/install-pip/usr/lib/python$(PYTHON2_VERSION)/site-packages/pip-$(PYTHON2_PIP_VERSION).dist-info \
		$(1)/usr/lib/python$(PYTHON2_VERSION)/site-packages/
endef

$(eval $(call Py2BasePackage,python2-pip, \
	, \
	DO_NOT_ADD_TO_PACKAGE_DEPENDS \
))
