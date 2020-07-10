#
# Copyright (C) 2015-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

# Note: include this after `include $(TOPDIR)/rules.mk in your package Makefile
#       if `python2-package.mk` is included, this will already be included

ifneq ($(__python2_host_mk_inc),1)
__python2_host_mk_inc=1

# For PYTHON2_VERSION
python2_mk_path:=$(dir $(lastword $(MAKEFILE_LIST)))
include $(python2_mk_path)python2-version.mk

HOST_PYTHON2_DIR:=$(STAGING_DIR_HOSTPKG)
HOST_PYTHON2_INC_DIR:=$(HOST_PYTHON2_DIR)/include/python$(PYTHON2_VERSION)
HOST_PYTHON2_LIB_DIR:=$(HOST_PYTHON2_DIR)/lib/python$(PYTHON2_VERSION)

HOST_PYTHON2_PKG_DIR:=$(HOST_PYTHON2_DIR)/lib/python$(PYTHON2_VERSION)/site-packages

HOST_PYTHON2_BIN:=$(HOST_PYTHON2_DIR)/bin/python$(PYTHON2_VERSION)

HOST_PYTHON2PATH:=$(HOST_PYTHON2_LIB_DIR):$(HOST_PYTHON2_PKG_DIR)

define HostPython2
	if [ "$(strip $(3))" == "HOST" ]; then \
		export PYTHONPATH="$(HOST_PYTHON2PATH)"; \
		export PYTHONDONTWRITEBYTECODE=0; \
	else \
		export PYTHONPATH="$(PYTHON2PATH)"; \
		export PYTHONDONTWRITEBYTECODE=1; \
		export _python_sysroot="$(STAGING_DIR)"; \
		export _python_prefix="/usr"; \
		export _python_exec_prefix="/usr"; \
	fi; \
	export PYTHONOPTIMIZE=""; \
	$(1) \
	$(HOST_PYTHON2_BIN) $(2);
endef

define host_python2_settings
	ARCH="$(HOST_ARCH)" \
	CC="$(HOSTCC)" \
	CCSHARED="$(HOSTCC) $(HOST_FPIC)" \
	CXX="$(HOSTCXX)" \
	LD="$(HOSTCC)" \
	LDSHARED="$(HOSTCC) -shared" \
	CFLAGS="$(HOST_CFLAGS)" \
	CPPFLAGS="$(HOST_CPPFLAGS) -I$(HOST_PYTHON2_INC_DIR)" \
	LDFLAGS="$(HOST_LDFLAGS) -lpython$(PYTHON2_VERSION) -Wl$(comma)-rpath=$(STAGING_DIR_HOSTPKG)/lib" \
	_PYTHON_HOST_PLATFORM=linux2
endef

# $(1) => commands to execute before running pythons script
# $(2) => python script and its arguments
# $(3) => additional variables
define Build/Compile/HostPy2RunHost
	$(call HostPython2, \
		$(if $(1),$(1);) \
		$(call host_python2_settings) \
		$(3) \
		, \
		$(2) \
		, \
		HOST \
	)
endef

# Note: I shamelessly copied this from Yousong's logic (from python-packages);
HOST_PYTHON2_PIP:=$(STAGING_DIR_HOSTPKG)/bin/pip$(PYTHON2_VERSION)

# $(1) => packages to install
define Build/Compile/HostPy2PipInstall
	$(call host_python2_settings) \
	$(HOST_PYTHON2_PIP) \
		--disable-pip-version-check \
		--cache-dir "$(DL_DIR)/pip-cache" \
		install \
		$(1)
endef

# $(1) => build subdir
# $(2) => additional arguments to setup.py
# $(3) => additional variables
define Build/Compile/HostPy2Mod
	$(call Build/Compile/HostPy2RunHost, \
		cd $(HOST_BUILD_DIR)/$(strip $(1)), \
		./setup.py $(2), \
		$(3))
endef

endif # __python2_host_mk_inc
