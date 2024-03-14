include $(TOPDIR)/rules.mk

PKG_NAME:=modemband
PKG_VERSION:=20240204
PKG_RELEASE:=1

PKG_LICENSE:=MIT
PKG_MAINTAINER:=Cezary Jackiewicz <cezary@eko.one.pl>

include $(INCLUDE_DIR)/package.mk

define Package/modemband
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=WWAN
  TITLE:=Setting LTE/5G bands for selected modems
  DEPENDS:=+sms-tool
  PKGARCH:=all
endef

define Build/Compile
endef

define Package/modemband/install
	$(CP) ./files/* $(1)
endef

$(eval $(call BuildPackage,modemband))
