# SDPX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2021-2022 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=amule
PKG_VERSION:=2.3.3
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/amule-project/amule.git
PKG_SOURCE_VERSION:=e26d06a6eeaf37c716a88a47890cb85b931a0538
PKG_MIRROR_HASH:=69a2a2eaa74fb87ab6da5223bae21113bcf7ab105f0e59fe793730ad716d9246

PKG_CONFIG_DEPEDS:= CONFIG_AMULE_CRYPTOPP_STATIC_LINKING

PKG_FIXUP:=autoreconf
PKG_BUILD_DEPENDS:=libcryptopp libgd
PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/amule
  SUBMENU:=P2P
  SECTION:=net
  CATEGORY:=Network
  TITLE:=A multi-platform eMule-like ed2k client
  URL:=http://www.amule.org/
  DEPENDS:=+antileech +libpng +libpthread +libncurses +libreadline +libwxbase \
	+libupnp +libbfd $(ICONV_DEPENDS) $(INTL_DEPENDS) \
	+!AMULE_CRYPTOPP_STATIC_LINKING:libcryptopp
endef

define Package/amule/config
config AMULE_CRYPTOPP_STATIC_LINKING
	bool "Link libcryptopp statically"
	default n
endef

define Download/AmuleWebUI
  URL:=https://github.com/MatteoRagni/AmuleWebUI-Reloaded/archive
  URL_FILE:=master.zip
  FILE:=AmuleWebUI.zip
  HASH:=83b17acd4744786bc1539fe102c4d7ecf49cec9f0358f3d6613663c6deb22d80
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	unzip $(DL_DIR)/AmuleWebUI.zip -d $(PKG_BUILD_DIR)
	sed -i s/"ajax.googleapis.com"/"ajax.lug.ustc.edu.cn"/g  $(PKG_BUILD_DIR)/AmuleWebUI-Reloaded-master/*.php
endef

TARGET_LDFLAGS += $(if $(ICONV_FULL),-liconv)

CONFIGURE_ARGS+= \
	--disable-static \
	--disable-geoip \
	--disable-rpath \
	--enable-ccache \
	--enable-optimize \
	--disable-profile \
	--disable-monolithic \
	--enable-amule-daemon \
	--enable-amulecmd \
	--enable-webserver \
	--disable-amule-gui \
	--disable-cas \
	--disable-wxcas \
	--disable-xas \
	--enable-ed2k \
	--disable-alc \
	--disable-alcc \
	--disable-fileview \
	--enable-mmap \
	--disable-plasmamule \
	--without-wxdebug \
	--enable-dlp \
	--enable-upnp \
	--without-gnu-malloc \
	--with-gnu-ld \
	--with-zlib="$(STAGING_DIR)/usr" \
	--with-gdlib-prefix="$(STAGING_DIR)/usr" \
	--with-libpng-prefix="$(STAGING_DIR)/usr" \
	--with-wx-prefix="$(STAGING_DIR)/usr" \
	--with-crypto-prefix="$(STAGING_DIR)/usr" \
	--with-libiconv-prefix="$(ICONV_PREFIX)" \
	--with-libintl-prefix="$(INTL_PREFIX)" \
	--with-libupnp-prefix="$(STAGING_DIR)/usr" \
	--disable-debug 

define Build/Configure
	cd $(PKG_BUILD_DIR); $(SHELL) autogen.sh
	$(call Build/Configure/Default)
endef

ifeq ($(CONFIG_AMULE_CRYPTOPP_STATIC_LINKING),y)
	SED_CMD:=sed
else
	SED_CMD:=true
endif

define Build/Compile
	$(SED_CMD) -i 's;^CRYPTOPP_LIBS.*;CRYPTOPP_LIBS \= "$(STAGING_DIR)/usr/lib/libcryptopp.a";g' \
		$(PKG_BUILD_DIR)/src/Makefile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		HOSTCC="$(HOSTCC)" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		all
endef

define Package/amule/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/amulecmd $(1)/usr/bin/amulecmd
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/amuled $(1)/usr/bin/amuled
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/amuleweb $(1)/usr/bin/amuleweb

	$(INSTALL_DIR) $(1)/usr/share
	$(CP) $(PKG_INSTALL_DIR)/usr/share/amule $(1)/usr/share/
	$(CP) $(PKG_BUILD_DIR)/AmuleWebUI-Reloaded-master $(1)/usr/share/amule/webserver/AmuleWebUI-Reloaded
endef

$(eval $(call Download,AmuleWebUI))
$(eval $(call BuildPackage,amule))
