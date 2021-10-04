include $(TOPDIR)/rules.mk

PKG_NAME:=ddns-scripts-dnspod-com
PKG_VERSION:=1.0.2
PKG_RELEASE:=1

PKG_LICENSE:=GPLv2
PKG_MAINTAINER:=Small_5

include $(INCLUDE_DIR)/package.mk

define Package/ddns-scripts-dnspod-com
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=IP Addresses and Names
  TITLE:=DDNS extension for Dnspod.com
  PKGARCH:=all
  DEPENDS:=ddns-scripts +wget-ssl +ca-certificates
endef

define Package/ddns-scripts-dnspod-com/description
  Dynamic DNS Client scripts extension for Dnspod.com
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/ddns-scripts-dnspod-com/install
	$(INSTALL_DIR) $(1)/usr/lib/ddns $(1)/usr/share/ddns/default
	$(INSTALL_BIN) $(CURDIR)/files/update_dnspod_com.sh $(1)/usr/lib/ddns
	$(INSTALL_DATA) $(CURDIR)/files/dnspod.com.json $(1)/usr/share/ddns/default
endef

define Package/ddns-scripts-dnspod-com/prerm
	#!/bin/sh
	# if NOT run buildroot then stop service
	[ -z "$${IPKG_INSTROOT}" ] && /etc/init.d/ddns stop >/dev/null 2>&1
	exit 0 # suppress errors
endef

$(eval $(call BuildPackage,ddns-scripts-dnspod-com))
