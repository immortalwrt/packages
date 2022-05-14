include $(TOPDIR)/rules.mk

PKG_NAME:=mhz
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=https://github.com/wtarreau/mhz.git
PKG_SOURCE_DATE:=2020-05-12
PKG_SOURCE_VERSION:=d1ed90e3523ab0300d6e7960eaaa49ef8c41845d
PKG_MIRROR_HASH:=0bbe8656ce35e0d675e63402c0687e5b1bd874710bfaec20045aa870073b1c63

include $(INCLUDE_DIR)/package.mk

define Package/mhz
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=CPU frequency measurement utility
  URL:=https://github.com/wtarreau/mhz
endef

define Package/mhz/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mhz $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,mhz))
