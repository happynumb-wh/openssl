#!/bin/sh

./Configure -ggdb3 -O0 linux-generic64 --cross-compile-prefix=riscv64-unknown-linux-gnu- --prefix=$PWD/.openssl shared no-asm no-threads --openssldir=openssl
make 