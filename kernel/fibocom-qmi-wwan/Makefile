include $(TOPDIR)/rules.mk

PKG_NAME:=fibocom-qmi-wwan
PKG_VERSION:=1.0.5
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@IMMORTALWRT
PKG_HASH:=107a82e4e81bcac0425368965432dd988e8e07c123a57f6ae63329cbf2ba39db

PKG_LICENSE:=GPL-2.0-only
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

define KernelPackage/usb-net-qmi-wwan-fibocom
  SUBMENU:=USB Support
  TITLE:=QMI WWAN driver for Fibocom modules
  DEPENDS:=+kmod-usb-net +kmod-usb-wdm
  FILES:=$(PKG_BUILD_DIR)/qmi_wwan_f.ko
  AUTOLOAD:=$(call AutoLoad,82,qmi_wwan_f)
endef

define Build/Compile
	+$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

$(eval $(call KernelPackage,usb-net-qmi-wwan-fibocom))
