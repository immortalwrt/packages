#!/bin/bash

export CURDIR="$(cd "$(dirname $0)"; pwd)"

TAG_INFO="$(curl -H "Authorization: $GITHUB_TOKEN" -sL "https://api.github.com/repos/shadowsocks/shadowsocks-rust/releases/latest")"
[ -n "$TAG_INFO" ] || exit 1

VERSION="$(jq -r ".tag_name" <<< "$TAG_INFO" | tr -d 'v')"
PKG_VERSION="$(awk -F "PKG_VERSION:=" '{print $2}' "$CURDIR/Makefile" | xargs)"
[ "$PKG_VERSION" != "$VERSION" ] || exit 0

for i in $(jq -r '.assets[].browser_download_url | select(contains("musl") and contains("sha256"))' <<< "$TAG_INFO"); do
	arch="$(awk -F '[-.]' '{print $9}' <<< "$i")"
	libc="$(awk -F '[-.]' '{print $12}' <<< "$i" | tr -d 'musl')"
	line="$(awk "/PKG_SOURCE:=.*\.$arch-.*$libc\./ {print NR}" "$CURDIR/Makefile")"
	[ -n "$line" ] || continue

	sha256="$(curl -fsSL "$i" | awk '{print $1}')" || exit 1
	sed -i "$((line + 1))s/PKG_HASH:=.*/PKG_HASH:=$sha256/" "$CURDIR/Makefile"
done

sed -i "s,PKG_VERSION:=.*,PKG_VERSION:=$VERSION,g" "$CURDIR/Makefile"
