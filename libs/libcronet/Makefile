# SPDX-License-Identifier: GPL-3.0-only
#
# Copyright (C) 2026 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=libcronet
PKG_VERSION=150.0.7871.63~$(call version_abbrev,$(PKG_SOURCE_VERSION))
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/SagerNet/naiveproxy.git
PKG_SOURCE_VERSION:=72a06c9fca0e2d228588c7f3074bf7efff3ff686
PKG_MIRROR_HASH:=79da434d2ca1149ec830269502c74d4d6f5aa9e3f77fe0e1c2dc42ec2a3c6c00

PKG_LICENSE:=BSD 3-Clause
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

PKG_BUILD_DEPENDS:=gn/host
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=no-mips16

ifneq ($(CONFIG_CPU_TYPE)," ")
  CPU_TYPE:=$(word 1, $(subst +," ,$(CONFIG_CPU_TYPE)))
  CPU_SUBTYPE:=$(word 2, $(subst +, ",$(CONFIG_CPU_TYPE)))
  ifeq ($(CPU_SUBTYPE),)
    CPU_SUBTYPE:=""
  endif
else
  CPU_TYPE:=""
  CPU_SUBTYPE:=""
endif

include $(INCLUDE_DIR)/package.mk

define Package/libcronet
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=The Chromium network stack library
  URL:=https://github.com/SagerNet/naiveproxy
  DEPENDS:=@!(arc||armeb||loongarch64||mips||mips64||powerpc||TARGET_gemini) $(ATOMIC64_DEPENDS)
endef

define Package/libcronet/description
  Cronet is the Chromium network stack made available to Android apps as a library.

  Cronet takes advantage of multiple technologies that reduce the latency and
  increase the throughput of the network requests that your app needs to work.
endef

ifneq ($(CONFIG_CCACHE),)
  export CCACHE_SLOPPINESS=time_macros
  export CCACHE_BASEDIR=$(PKG_BUILD_DIR)/src
  export CCACHE_CPP2=yes
  export naive_ccache_flags=cc_wrapper="$(CCACHE)"
endif

CLANG_VER:=23-init-10931-g20b6ec66-11
CLANG_FILE:=clang-llvmorg-$(CLANG_VER).tar.xz
define Download/CLANG
	URL:=https://commondatastorage.googleapis.com/chromium-browser-clang/Linux_x64
	URL_FILE:=$(CLANG_FILE)
	FILE:=$(CLANG_FILE)
	HASH:=de584381536aa5ba2403033c4f8b70f3c39c2e5d7fa87c953b7fd8bfbba0ee2a
endef

PGO_VER:=7871-1782236690-ee033e4bf26c147ed0557fd905d416dc66bc7545-3d4da56162112271e9a86f91f4696c964516a649
PGO_FILE:=chrome-linux-$(PGO_VER).profdata
define Download/PGO_PROF
	URL:=https://storage.googleapis.com/chromium-optimization-profiles/pgo_profiles
	URL_FILE:=$(PGO_FILE)
	FILE:=$(PGO_FILE)
	HASH:=63118ef73e3d7fe033ef94c8b3d1751174504c32ee8fdecc081e4a17491926da
endef

define Build/Prepare
	$(call Build/Prepare/Default)

	( \
		pushd $(PKG_BUILD_DIR)/src ; \
		mkdir -p "chrome/build/pgo_profiles" ; \
		$(CP) "$(DL_DIR)/$(PGO_FILE)" "chrome/build/pgo_profiles" ; \
		mkdir -p "third_party/llvm-build/Release+Asserts" ; \
		$(TAR) -xJf "$(DL_DIR)/$(CLANG_FILE)" -C "third_party/llvm-build/Release+Asserts" ; \
		echo -e "llvmorg-$(CLANG_VER)" > "third_party/llvm-build/Release+Asserts/cr_build_revision" ; \
		popd ; \
	)
endef

define Build/Configure
	( \
		pushd "$(PKG_BUILD_DIR)/src" ; \
		. ../init_env.sh "$(ARCH)" $(CPU_TYPE) $(CPU_SUBTYPE) "$(TOOLCHAIN_ROOT_DIR)" ; \
		export naive_flags+=" $$$${naive_ccache_flags}" ; \
		mkdir -p "out" ; \
		gn gen "out/Release" --args="$$$${naive_flags}" --script-executable="$(PYTHON)" ; \
		popd ; \
	)
endef

define Build/Compile
	+$(NINJA) -C "$(PKG_BUILD_DIR)/src/out/Release" cronet
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) \
		$(PKG_BUILD_DIR)/src/components/cronet/native/include/cronet_c.h \
		$(PKG_BUILD_DIR)/src/components/cronet/native/include/cronet_export.h \
		$(PKG_BUILD_DIR)/src/components/cronet/native/generated/cronet.idl_c.h \
		$(PKG_BUILD_DIR)/src/components/grpc_support/include/bidirectional_stream_c.h \
		$(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/src/out/Release/libcronet.so $(1)/usr/lib/
endef

define Package/libcronet/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/src/out/Release/libcronet.so $(1)/usr/lib/
endef

$(eval $(call Download,CLANG))
$(eval $(call Download,PGO_PROF))

$(eval $(call BuildPackage,libcronet))
