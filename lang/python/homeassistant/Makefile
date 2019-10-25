#
# Copyright (C) 2019 CZ.NIC, z. s. p. o. (https://www.nic.cz/)
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=homeassistant
PKG_VERSION:=0.98.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://files.pythonhosted.org/packages/source/h/homeassistant
PKG_HASH:=7f8a6a011cf1cf2254a471f0eae1bedaad6dba1dcf3ab67f453d9a80d73ee477

PKG_MAINTAINER:=Josef Schlehofer <pepe.schlehofer@gmail.com>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE.md
PKG_CPE_ID:=cpe:/a:home-assistant:home-assistant

include $(INCLUDE_DIR)/package.mk
include ../python3-package.mk

define Package/$(PKG_NAME)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Home Assistant
  URL:=https://www.home-assistant.io/
  DEPENDS:= \
    +python3-aiohttp \
    +python3-aiohttp-cors \
    +python3-astral \
    +python3-async-timeout \
    +python3-attrs \
    +python3-bcrypt \
    +python3-certifi \
    +python3-cryptography \
    +python3-ifaddr \
    +python3-importlib-metadata \
    +python3-jinja2 \
    +python3-netdisco \
    +python3-pip \
    +python3-pyjwt \
    +python3-pyotp \
    +python3-pytz \
    +python3-slugify \
    +python3-sqlalchemy \
    +python3-requests \
    +python3-ruamel-yaml \
    +python3-voluptuous \
    +python3-voluptuous-serialize \
    +python3-yaml \
    +python3-zeroconf
  VARIANT:=python3
endef

define Package/$(PKG_NAME)/description
  Home Assistant is a home automation platform running on Python 3.
  It is able to track and control all devices at home and offer a platform for automating control.

  It requires a minimum of 1 GB of RAM.
endef

define Py3Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/hass.init $(1)/etc/init.d/hass
endef

$(eval $(call Py3Package,$(PKG_NAME)))
$(eval $(call BuildPackage,$(PKG_NAME)))
$(eval $(call BuildPackage,$(PKG_NAME)-src))
