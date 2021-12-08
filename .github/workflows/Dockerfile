ARG ARCH=x86-64
ARG BRANCH=master
FROM immortalwrt/rootfs:$ARCH-$BRANCH

ADD entrypoint.sh /entrypoint.sh

CMD ["/entrypoint.sh"]
