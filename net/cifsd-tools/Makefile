include $(TOPDIR)/rules.mk

PKG_NAME:=cifsd-tools
PKG_VERSION:=3.2.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/cifsd-team/cifsd-tools/archive/$(PKG_VERSION)/
PKG_HASH:=acb4d97cbb0b22ad42ed1536bdd2c28af2a3c698664c058da59a644d5e6df599

PKG_MAINTAINER:=Andy Walsh <andy.walsh44+github@gmail.com>
PKG_LICENSE:=GPL-2.0-or-later
PKG_LICENSE_FILES:=COPYING

PKG_FIXUP:=autoreconf
PKG_REMOVE_FILES:=autogen.sh
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define Package/cifsd-tools
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Filesystem
  TITLE:=Kernel CIFS/SMB server support and userspace tools
  URL:=https://github.com/cifsd-team/cifsd-tools
  DEPENDS:=+kmod-fs-cifsd +glib2 +libnl-core +libnl-genl
endef

define Package/cifsd-tools/description
  Userspace tools (cifsd, cifsuseradd, cifsshareadd) for the CIFS/SMB kernel fileserver.
  The config file location is /etc/cifs/smb.conf
endef

define Package/cifsd-tools/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libcifsdtools.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/{cifsuseradd,cifsshareadd,cifsd} $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/cifs $(1)/etc/init.d
	$(INSTALL_CONF) ./files/cifsd.config $(1)/etc/config/cifsd
	$(INSTALL_DATA) ./files/smb.conf.template $(1)/etc/cifs/
	$(INSTALL_BIN) ./files/cifsd.init $(1)/etc/init.d/cifsd
	# copy examples until we have a wiki page
	$(INSTALL_DATA) ./files/cifsd.config.example $(1)/etc/cifs/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/Documentation/configuration.txt $(1)/etc/cifs/
endef

define Package/cifsd-tools/conffiles
/etc/config/cifsd
/etc/cifs/smb.conf.template
/etc/cifs/smb.conf
/etc/cifs/cifsdpwd.db
endef

$(eval $(call BuildPackage,cifsd-tools))
