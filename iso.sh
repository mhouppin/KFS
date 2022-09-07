#!/bin/sh

set -e

. ./build.sh

mkdir -p isodir/boot/grub

cp sysroot/boot/vault.kernel isodir/boot/vault.kernel

cat > isodir/boot/grub/grub.cfg << EOF
menuentry "vault" {
    multiboot /boot/vault.kernel
}
EOF

grub-mkrescue -o vault.iso isodir
