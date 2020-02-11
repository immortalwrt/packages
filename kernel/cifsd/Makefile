include $(TOPDIR)/rules.mk

PKG_NAME:=cifsd
PKG_VERSION:=3.1.3
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/cifsd-team/cifsd/archive/$(PKG_VERSION)/
PKG_HASH:=c3c4531d3806117218d23e0552edfe883f978a00b7293180dd2919694102fcb9

PKG_MAINTAINER:=Andy Walsh <andy.walsh44+github@gmail.com>
PKG_LICENSE:=GPL-2.0-or-later
PKG_LICENSE_FILES:=COPYING

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/fs-cifsd
	SUBMENU:=Filesystems
	TITLE:=CIFS/SMB kernel server support
	URL:=https://github.com/cifsd-team/cifsd
	FILES:=$(PKG_BUILD_DIR)/cifsd.ko
	DEPENDS:= \
		+kmod-nls-base \
		+kmod-nls-utf8 \
		+kmod-crypto-md4 \
		+kmod-crypto-md5 \
		+kmod-crypto-hmac \
		+kmod-crypto-ecb \
		+kmod-crypto-des \
		+kmod-crypto-sha256 \
		+kmod-crypto-cmac \
		+kmod-crypto-sha512 \
		+kmod-crypto-aead \
		+kmod-crypto-ccm \
		+kmod-crypto-gcm
endef

define KernelPackage/fs-cifsd/description
	Kernel module for a SMBv(1,)2,3 fileserver.
endef

define KernelPackage/fs-cifsd/config
config CIFSD_SMB_INSECURE_SERVER
	bool "Support for insecure SMB1/CIFS and SMB2.0 protocols"
	depends on PACKAGE_kmod-fs-cifsd
	help
		This enables deprecated insecure protocols dialects: SMB1/CIFS and SMB2.0.
	default y
endef

ifeq ($(CONFIG_CIFSD_SMB_INSECURE_SERVER),y)
PKG_EXTRA_KCONFIG:=CONFIG_SMB_INSECURE_SERVER=y
EXTRA_CFLAGS += -DCONFIG_SMB_INSECURE_SERVER=1
endif

define Build/Compile
	$(KERNEL_MAKE) SUBDIRS="$(PKG_BUILD_DIR)" \
	EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
	$(PKG_EXTRA_KCONFIG) \
	CONFIG_CIFS_SERVER=m \
	modules
endef

$(eval $(call KernelPackage,fs-cifsd))
