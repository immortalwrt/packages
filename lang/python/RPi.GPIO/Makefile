# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=RPi.GPIO
PKG_VERSION:=0.7.1
PKG_RELEASE:=1

PYPI_NAME:=RPi.GPIO
PKG_HASH:=cd61c4b03c37b62bba4a5acfea9862749c33c618e0295e7e90aa4713fb373b70

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENCE.txt
PKG_MAINTAINER:=Hirokazu MORIKAWA <morikw2@gmail.com>

PKG_BUILD_DEPENDS:=python-installer/host python-setuptools/host

PYTHON3_PKG_WHEEL_NAME:=rpi_gpio

include ../pypi.mk
include $(INCLUDE_DIR)/package.mk
include ../python3-package.mk

PYTHON3_PKG_SETUP_ARGS:=

define Package/python3-RPi.GPIO
  SECTION:=lang
  CATEGORY:=Languages
  SUBMENU:=Python
  URL:=https://sourceforge.net/projects/raspberry-gpio-python/
  TITLE:=python3-RPi.GPIO
  DEPENDS:=+python3-light
endef

define Package/python3-RPi.GPIO/description
  A module to control Raspberry Pi GPIO channels.
endef

$(eval $(call Py3Package,python3-RPi.GPIO))
$(eval $(call BuildPackage,python3-RPi.GPIO))
#$(eval $(call BuildPackage,python3-RPi.GPIO-src))
