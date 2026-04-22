#!/bin/sh

case "$1" in
psqlodbca)
	[ -f /usr/lib/psqlodbca.so ] || { echo "FAIL: psqlodbca.so not found"; exit 1; }
	echo "psqlodbca OK"
	;;
psqlodbcw)
	[ -f /usr/lib/psqlodbcw.so ] || { echo "FAIL: psqlodbcw.so not found"; exit 1; }
	echo "psqlodbcw OK"
	;;
esac
