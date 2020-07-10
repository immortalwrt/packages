#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Package/python2-setuptools
$(call Package/python2/Default)
  TITLE:=Python $(PYTHON2_VERSION) setuptools module
  VERSION:=$(PYTHON2_SETUPTOOLS_VERSION)-$(PYTHON2_SETUPTOOLS_PKG_RELEASE)
  LICENSE:=MIT
  LICENSE_FILES:=LICENSE
#  CPE_ID:=cpe:/a:python:setuptools # not currently handled this way by uscan
  DEPENDS:=+python2 +python2-pkg-resources
endef

define Py2Package/python2-setuptools/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/usr/lib/python$(PYTHON2_VERSION)/site-packages
	$(CP) $(PKG_BUILD_DIR)/install-setuptools/usr/bin/easy_install-* $(1)/usr/bin
	$(LN) easy_install-$(PYTHON2_VERSION) $(1)/usr/bin/easy_install-2
	$(CP) \
		$(PKG_BUILD_DIR)/install-setuptools/usr/lib/python$(PYTHON2_VERSION)/site-packages/setuptools \
		$(PKG_BUILD_DIR)/install-setuptools/usr/lib/python$(PYTHON2_VERSION)/site-packages/setuptools-$(PYTHON2_SETUPTOOLS_VERSION).dist-info \
		$(PKG_BUILD_DIR)/install-setuptools/usr/lib/python$(PYTHON2_VERSION)/site-packages/easy_install.py \
		$(1)/usr/lib/python$(PYTHON2_VERSION)/site-packages
endef

$(eval $(call Py2BasePackage,python2-setuptools, \
	, \
	DO_NOT_ADD_TO_PACKAGE_DEPENDS \
))
