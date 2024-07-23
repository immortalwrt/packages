include $(TOPDIR)/rules.mk

PKG_NAME:=7z
PKG_VERSION:=24.05
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)$(subst .,,$(PKG_VERSION))-src.tar.xz
PKG_SOURCE_URL:=https://7-zip.org/a/
PKG_HASH:=63f341cf80b8d287c6e945519b3da0fa75553c85572a471b7fa6e68f9a90b790

PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>
PKG_LICENSE:=LGPL-2.1-or-later BSD-3-Clause unRAR
PKG_LICENSE_FILES:=DOC/License.txt DOC/copying.txt DOC/unRarLicense.txt
PKG_CPE_ID:=cpe:/a:7-zip:7-zip

HOST_BUILD_PARALLEL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define Package/7z
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Compression
  TITLE:=File archiver with a high compression ratio
  URL:=https://7-zip.org/
  DEPENDS:=+libstdcpp
endef

MAKE_PATH:=CPP/7zip/Bundles/Alone2

define Host/Compile
	+$(MAKE) $(PKG_JOBS) -C $(HOST_BUILD_DIR)/$(MAKE_PATH) \
		-f ../../cmpl_gcc.mak \
		CC="$(HOSTCC) $(HOST_CFLAGS)" \
		CXX="$(HOSTCXX) $(HOST_CXXFLAGS)"
endef

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR)/$(MAKE_PATH) \
		-f ../../cmpl_gcc.mak \
		CC="$(TARGET_CC) $(TARGET_CFLAGS)" \
		CXX="$(TARGET_CXX) $(TARGET_CXXFLAGS)"
endef

define Host/Clean
	$(RM) $(STAGING_DIR_HOSTPKG)/bin/7z $(STAGING_DIR_HOSTPKG)/bin/7zz
endef

define Host/Install
	$(INSTALL_DIR) $(STAGING_DIR_HOSTPKG)/bin
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/$(MAKE_PATH)/b/g/7zz $(STAGING_DIR_HOSTPKG)/bin/
	$(LN) 7zz $(STAGING_DIR_HOSTPKG)/bin/7z
endef

define Package/7z/install
	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(MAKE_PATH)/b/g/7zz $(1)/usr/bin/
	$(LN) 7zz $(1)/usr/bin/7z
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,7z))
