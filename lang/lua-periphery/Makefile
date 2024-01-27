include $(TOPDIR)/rules.mk

PKG_NAME:=lua-periphery
PKG_VERSION:=2.4.2
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/vsergeev/lua-periphery.git
PKG_SOURCE_VERSION:=v$(PKG_VERSION)
PKG_MIRROR_HASH:=395e610a5137d0ff1187d75e03ae829c85bc7689e0fe4732d6aff8886b7e9384

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_FLAGS:=gc-sections
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/lua-periphery
  SUBMENU:=Lua
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=A Lua library for peripheral I/O in Linux
  URL:=https://github.com/vsergeev/lua-periphery
  DEPENDS:=+lua
endef

define Package/lua-periphery/description
  lua-periphery is a library for GPIO, LED, PWM, SPI, I2C, MMIO, and
  Serial peripheral I/O interface access in userspace Linux.
endef

define Package/lua-periphery/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(CP) $(PKG_BUILD_DIR)/periphery.so* $(1)/usr/lib/lua/
endef

$(eval $(call BuildPackage,lua-periphery))
