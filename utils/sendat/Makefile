include $(TOPDIR)/rules.mk

PKG_NAME:=sendat
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/ouyangzq/sendat.git
PKG_SOURCE_DATE:=2023-10-26
PKG_SOURCE_VERSION:=c830885db5bb8ae2dcb10b1bfeab481f14935dd1
PKG_MIRROR_HASH:=f064a73d19e6c39dec908f22622651555bc7305c155768b66834dbbd23ba13b3

include $(INCLUDE_DIR)/package.mk

define Package/sendat
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=WWAN
  TITLE:=Send AT commands to serial
endef

MAKE_PATH:=src

define Package/sendat/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/sendat $(1)/usr/bin/
endef

$(eval $(call BuildPackage,sendat))
