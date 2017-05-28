#!/bin/sh

set -e

SRCDIR=`pwd`
DESTDIR=`pwd`

mkdir -p build
mkdir -p build/wine-host
mkdir -p build/qemu

# Build the Host (e.g. arm64) wine
cd build/wine-host
$SRCDIR/wine/configure --prefix=$DESTDIR/build/install
make -j 4
make install

# Bleh. WINEBUILD=XXX means that you can't simply run "make" inside qemu's output dir.
# You need to set WINEBUILD in the same way first.

# Build qemu
cd ../qemu
WINEBUILD=$DESTDIR/build/install/bin/winebuild CC="$DESTDIR/build/install/bin/winegcc -lpthread -lpthread_nonshared -DWINE_NOWINSOCK" CXX="$DESTDIR/build/install/bin/wineg++ -lpthread -lpthread_nonshared -DWINE_NOWINSOCK" $SRCDIR/qemu/configure --disable-bzip2 --disable-libusb --disable-sdl --disable-snappy --disable-virtfs --disable-opengl --python=/usr/bin/python2.7 --disable-xen --disable-lzo --disable-qom-cast-debug --disable-vnc --disable-seccomp --disable-strip --disable-hax --disable-gnutls --disable-nettle --disable-replication --disable-tpm --disable-gtk --disable-gcrypt --disable-linux-aio --disable-system --without-pixman --disable-tools --disable-linux-user --enable-windows-user
WINEBUILD=$DESTDIR/build/install/bin/winebuild make

# Build the wrapper DLLs

# Cross-compile the Wine DLLs for x86 to quick-start higher level DLLs without having to wrap everything
# Copy selected higher level DLLs into the guest DLL directory.
