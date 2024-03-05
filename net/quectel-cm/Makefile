include $(TOPDIR)/rules.mk

PKG_NAME:=quectel-cm
PKG_VERSION:=1.6.5
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@IMMORTALWRT
PKG_HASH:=d2d888d457ef7fd02249c42b2f56d77513285957cd0c02f240a390de1f23e3fd

PKG_LICENSE:=Public Domain
PKG_LICENSE_FILES:=NOTICE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/quectel-cm
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=WWAN
  TITLE:=Qconnector Manager for Quectel WWAN modules
  DEPENDS:= \
    +kmod-usb-net-cdc-mbim \
    +kmod-usb-net-qmi-wwan \
    +kmod-usb-net-qmi-wwan-fibocom \
    +kmod-usb-net-qmi-wwan-quectel \
    +kmod-usb-serial-option
endef

define Package/quectel-cm/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/quectel-CM $(1)/usr/bin/quectel-cm
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/quectel-{mbim,qmi}-proxy $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/lib/netifd/proto
	$(INSTALL_BIN) ./files/quectel.sh $(1)/lib/netifd/proto/

	$(INSTALL_DIR) $(1)/etc/hotplug.d/net
	$(INSTALL_BIN) ./files/smp-affinity-mhi-pcie.sh $(1)/etc/hotplug.d/net/21-smp-affinity-mhi-pcie
	$(INSTALL_BIN) ./files/smp-affinity-qmi-usb.sh $(1)/etc/hotplug.d/net/22-smp-affinity-qmi-usb
endef

$(eval $(call BuildPackage,quectel-cm))
