# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=psutil
PKG_VERSION:=5.7.2
PKG_RELEASE:=1

PYPI_NAME:=$(PKG_NAME)
PKG_HASH:=90990af1c3c67195c44c9a889184f84f5b2320dce3ee3acbd054e3ba0b4a7beb

PKG_MAINTAINER:=CN_SZTL <cnsztl@project-openwrt.eu.org>
PKG_LICENSE:=BSD-3-Clause
PKG_LICENSE_FILES:=LICENSE

include ../pypi.mk
include $(INCLUDE_DIR)/package.mk
include ../python3-package.mk

define Package/python3-psutil
  SECTION:=lang
  CATEGORY:=Languages
  SUBMENU:=Python
  TITLE:=Cross-platform lib for process and system monitoring in Python
  URL:=https://github.com/giampaolo/psutil
  DEPENDS:=+python3-light
endef

define Package/python3-psutil/description
  psutil (process and system utilities) is a cross-platform library for
  retrieving information on running processes and system utilization (CPU,
  memory, disks, network, sensors) in Python. It is useful mainly for system
  monitoring, profiling and limiting process resources and management of
  running processes. It implements many functionalities offered by classic
  UNIX command line tools such as ps, top, iotop, lsof, netstat, ifconfig,
  free and others.
endef

$(eval $(call Py3Package,python3-psutil))
$(eval $(call BuildPackage,python3-psutil))
$(eval $(call BuildPackage,python3-psutil-src))
