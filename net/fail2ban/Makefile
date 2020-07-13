#
# Copyright (C) 2020 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=fail2ban
PKG_VERSION:=0.11.1
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/fail2ban/fail2ban/archive/
PKG_HASH:=71d2a52b66bb0f87ac3812246bdd3819ec561913cd44afd39130a342f043aa6d
PKG_BUILD_DIR:=$(BUILD_DIR)/fail2ban-$(PKG_VERSION)

PKG_MAINTAINER:=[CTCGFW]Project OpenWrt / CN_SZTL <cnsztl@project-openwrt.eu.org>
PKG_LICENSE:=GPL-2.0-later
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk
include ../../lang/python/python3-package.mk

define Package/fail2ban
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=SSH
  TITLE:=Daemon to ban hosts that cause multiple authentication errors
  URL:=https://www.fail2ban.org
  DEPENDS:= \
    +python3 \
    +python3-setuptools
endef

define Package/fail2ban/description
  Fail2Ban scans log files like /var/log/auth.log and bans IP addresses
  conducting too many failed login attempts. It does this by updating system firewall
  rules to reject new connections from those IP addresses, for a configurable
  amount of time. Fail2Ban comes out-of-the-box ready to read many standard log files,
  such as those for sshd and Apache, and is easily configured to read
  any log file of your choosing, for any error you wish.
endef

define Package/fail2ban/install
	$(INSTALL_DIR) $(1)
	rsync $(PKG_INSTALL_DIR)/* $(1)/
endef

$(eval $(call Py3Package,fail2ban))
$(eval $(call BuildPackage,fail2ban))
$(eval $(call BuildPackage,fail2ban-src))
