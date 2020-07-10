#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

# Note: include this after `include $(TOPDIR)/rules.mk in your package Makefile

python2_mk_path:=$(dir $(lastword $(MAKEFILE_LIST)))
include $(python2_mk_path)python2-host.mk

PYTHON2_DIR:=$(STAGING_DIR)/usr
PYTHON2_BIN_DIR:=$(PYTHON2_DIR)/bin
PYTHON2_INC_DIR:=$(PYTHON2_DIR)/include/python$(PYTHON2_VERSION)
PYTHON2_LIB_DIR:=$(PYTHON2_DIR)/lib/python$(PYTHON2_VERSION)

PYTHON2_PKG_DIR:=/usr/lib/python$(PYTHON2_VERSION)/site-packages

PYTHON2:=python$(PYTHON2_VERSION)

PYTHON2PATH:=$(PYTHON2_LIB_DIR):$(STAGING_DIR)/$(PYTHON2_PKG_DIR):$(PKG_INSTALL_DIR)/$(PYTHON2_PKG_DIR)

# These configure args are needed in detection of path to Python header files
# using autotools.
CONFIGURE_ARGS += \
	_python_sysroot="$(STAGING_DIR)" \
	_python_prefix="/usr" \
	_python_exec_prefix="/usr"

PKG_USE_MIPS16:=0
# This is required in addition to PKG_USE_MIPS16:=0 because otherwise MIPS16
# flags are inherited from the Python base package (via sysconfig module)
ifdef CONFIG_USE_MIPS16
  TARGET_CFLAGS += -mno-mips16 -mno-interlink-mips16
endif

define Py2Shebang
$(SED) "1"'!'"b;s,^#"'!'".*python.*,#"'!'"/usr/bin/python2," -i --follow-symlinks $(1)
endef

define Py2Package

  define Package/$(1)-src
    $(call Package/$(1))
    DEPENDS:=
    CONFLICTS:=
    PROVIDES:=
    EXTRA_DEPENDS:=
    TITLE+= (sources)
    USERID:=
    MENU:=
  endef

  define Package/$(1)-src/description
    $(call Package/$(1)/description).
    (Contains the Python2 sources for this package).
  endef

  # Add default PyPackage filespec none defined
  ifndef Py2Package/$(1)/filespec
    define Py2Package/$(1)/filespec
      +|$(PYTHON2_PKG_DIR)
    endef
  endif

  ifndef Py2Package/$(1)/install
    define Py2Package/$(1)/install
		if [ -d $(PKG_INSTALL_DIR)/usr/bin ]; then \
			$(INSTALL_DIR) $$(1)/usr/bin ; \
			$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $$(1)/usr/bin/ ; \
		fi
    endef
  endif

  ifndef Package/$(1)/install
  $(call shexport,Py2Package/$(1)/filespec)

  define Package/$(1)/install
	$$(call Py2Package/$(1)/install,$$(1))
	$(SHELL) $(python2_mk_path)python2-package-install.sh "2" \
		"$(PKG_INSTALL_DIR)" "$$(1)" \
		"$(HOST_PYTHON2_BIN)" "$$(2)" \
		"$$$$$$$$$$(call shvar,Py2Package/$(1)/filespec)" && \
	if [ -d "$$(1)/usr/bin" ]; then \
		$(call Py2Shebang,$$(1)/usr/bin/*) ; \
	fi
  endef

  define Package/$(1)-src/install
	$$(call Package/$(1)/install,$$(1),sources)
  endef
  endif # Package/$(1)/install
endef

# $(1) => commands to execute before running pythons script
# $(2) => python script and its arguments
# $(3) => additional variables
define Build/Compile/HostPy2RunTarget
	$(call HostPython2, \
		$(if $(1),$(1);) \
		CC="$(TARGET_CC)" \
		CCSHARED="$(TARGET_CC) $(FPIC)" \
		CXX="$(TARGET_CXX)" \
		LD="$(TARGET_CC)" \
		LDSHARED="$(TARGET_CC) -shared" \
		CFLAGS="$(TARGET_CFLAGS)" \
		CPPFLAGS="$(TARGET_CPPFLAGS) -I$(PYTHON2_INC_DIR)" \
		LDFLAGS="$(TARGET_LDFLAGS) -lpython$(PYTHON2_VERSION)" \
		_PYTHON_HOST_PLATFORM=linux2 \
		__PYVENV_LAUNCHER__="/usr/bin/$(PYTHON2)" \
		$(3) \
		, \
		$(2) \
	)
endef

# $(1) => build subdir
# $(2) => additional arguments to setup.py
# $(3) => additional variables
define Build/Compile/Py2Mod
	$(INSTALL_DIR) $(PKG_INSTALL_DIR)/$(PYTHON2_PKG_DIR)
	$(call Build/Compile/HostPy2RunTarget, \
		cd $(PKG_BUILD_DIR)/$(strip $(1)), \
		./setup.py $(2), \
		$(3))
endef

PYTHON2_PKG_SETUP_DIR ?=
PYTHON2_PKG_SETUP_GLOBAL_ARGS ?=
PYTHON2_PKG_SETUP_ARGS ?= --single-version-externally-managed
PYTHON2_PKG_SETUP_VARS ?=

define Py2Build/Compile/Default
	$(if $(HOST_PYTHON2_PACKAGE_BUILD_DEPENDS),
		$(call Build/Compile/HostPy2PipInstall,$(HOST_PYTHON2_PACKAGE_BUILD_DEPENDS))
	)
	$(call Build/Compile/Py2Mod, \
		$(PYTHON2_PKG_SETUP_DIR), \
		$(PYTHON2_PKG_SETUP_GLOBAL_ARGS) \
		install --prefix="/usr" --root="$(PKG_INSTALL_DIR)" \
		$(PYTHON2_PKG_SETUP_ARGS), \
		$(PYTHON2_PKG_SETUP_VARS) \
	)
endef

Py2Build/Compile=$(Py2Build/Compile/Default)

ifeq ($(BUILD_VARIANT),python2)
define Build/Compile
	$(call Py2Build/Compile)
endef
endif # python2
