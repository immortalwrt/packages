#!/bin/bash

set -x

function urldecode() { : "${*//+/ }"; echo -e "${_//%/\\x}"; }

export CURDIR="$(cd "$(dirname $0)"; pwd)"

TAG_INFO="$(curl -H "Authorization: $GITHUB_TOKEN" -sL "https://api.github.com/repos/zfl9/chinadns-ng/releases/latest")"
[ -n "$TAG_INFO" ] || exit 1

VERSION="$(jq -r ".tag_name" <<< "$TAG_INFO")"
PKG_VERSION="$(awk -F "PKG_VERSION:=" '{print $2}' "$CURDIR/Makefile" | xargs)"
[ "$PKG_VERSION" != "$VERSION" ] || exit 0

for i in $(jq -r '.assets[].browser_download_url | select(contains("chinadns-ng%2B"))' <<< "$TAG_INFO"); do
	i="$(urldecode "$i")"

	arch="$(awk -F '@' '{printf "%s@%s", $2, $3}' <<< "$i")"
	line="$(sed -n "/PKG_SOURCE_URL_FILE:=.*$arch@/=" "$CURDIR/Makefile")"
	[ -n "$line" ] || continue

	sha256="$(curl -fsSL "$i" | sha256sum | awk '{print $1}')" || exit 1
	sed -i "$((line + 1))s/PKG_HASH:=.*/PKG_HASH:=$sha256/" "$CURDIR/Makefile"
done

sed -i "s,PKG_VERSION:=.*,PKG_VERSION:=$VERSION,g" "$CURDIR/Makefile"

# 仅获取 armv5 的 2024.10.14 版本
DOWN_VERSION="$(awk -F ':=' '/DOWN_VERSION*:/{count++; if (count == 2) print $2}' "$CURDIR/Makefile" | xargs)"
if [ -n "$DOWN_VERSION" ]; then
    # 获取指定版本的信息
    TAG_INFO="$(curl -H "Authorization: $GITHUB_TOKEN" -sL "https://api.github.com/repos/zfl9/chinadns-ng/releases/tags/$DOWN_VERSION")"
    [ -n "$TAG_INFO" ] || exit 1

    # 提取版本号
    VERSION="$(jq -r ".tag_name" <<< "$TAG_INFO")"
    [ "$DOWN_VERSION" == "$VERSION" ] || exit 0

    # 只处理包含 v5t 的版本
    for i in $(jq -r '.assets[].browser_download_url | select(contains("chinadns-ng%2Bwolfssl%40") and contains("%2Bv5t%2B"))' <<< "$TAG_INFO"); do
        i="$(urldecode "$i")"

        arch="$(awk -F '@' '{printf "%s@%s", $2, $3}' <<< "$i")"
        line="$(sed -n "/PKG_SOURCE_URL_FILE:=.*wolfssl@$arch@/=" "$CURDIR/Makefile")"
        [ -n "$line" ] || continue

        sha256="$(curl -fsSL "$i" | sha256sum | awk '{print $1}')"  || exit 1
        sed -i "$((line + 1))s/PKG_HASH:=.*/PKG_HASH:=$sha256/" "$CURDIR/Makefile"
    done
fi
