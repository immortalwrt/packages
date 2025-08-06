include $(TOPDIR)/rules.mk

PKG_NAME:=sub-web
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/CareyWang/sub-web.git
PKG_SOURCE_DATE:=2024-08-07
PKG_SOURCE_VERSION:=c47bbabe4b1e41803527a3e79d07985416ae8402
PKG_MIRROR_HASH:=6f2d8cec60a7e4199e76845b21f1cc065385e1e1f34cd08c3df41ad1ec9be4cc

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=node/host node-yarn/host

include $(INCLUDE_DIR)/package.mk

define Package/sub-web
  SECTION:=net
  CATEGORY:=Network
  URL:=https://github.com/CareyWang/sub-web
  TITLE:=A WebUI for generating proxy subscription url
  DEPENDS:=+subconverter
  PKGARCH:=all
endef

define Package/sub-web/description
  Based on vue-cli and subconverter, for generating proxy subscription
  url automatically.
endef

define Build/Compile
	( \
		pushd "$(PKG_BUILD_DIR)"; \
		yarn install; \
		NODE_OPTIONS=--openssl-legacy-provider yarn build; \
		popd ; \
	)
endef

define Package/sub-web/install
	$(INSTALL_DIR) $(1)/www/sub-web
	$(CP) $(PKG_BUILD_DIR)/dist/* $(1)/www/sub-web/
endef

$(eval $(call BuildPackage,sub-web))
