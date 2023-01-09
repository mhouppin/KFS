include build-aux/hostarch.mk

ARCH ?= $(HOSTARCH)

SRCARCH := $(ARCH)

ifeq ($(ARCH),i386)
	SRCARCH := x86
endif
ifeq ($(ARCH),x86_64)
	SRCARCH := x86
endif

include arch/$(SRCARCH)/config.mk

# Additional code in case the LLVM installation has a prefix or suffix
ifneq ($(LLVM),)
	ifneq ($(filter %/,$(LLVM)),)
		LLVM_PREFIX := $(LLVM)
	else ifneq ($(filter -%,$(LLVM)),)
		LLVM_SUFFIX := $(LLVM)
	endif

	HOSTCC = $(LLVM_PREFIX)clang$(LLVM_SUFFIX)
else
	HOSTCC = gcc
endif

PREFIX := /usr
EXEC_PREFIX := $(PREFIX)
BOOTDIR := /boot
LIBDIR := $(EXEC_PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include

CROSS_TOOLCHAIN_PREFIX ?=
CFLAGS ?= -O2 -g
CPPFLAGS ?=

SYSROOT := $(shell pwd)/sysroot

CPP = $(CC) -E

# TODO: uncomment this later
#include arch/$(SRCARCH)/config.mk

ifneq ($(LLVM),)
	CC      := $(LLVM_PREFIX)clang$(LLVM_SUFFIX)
	LD      := $(LLVM_PREFIX)ld.lld$(LLVM_SUFFIX)
	AR      := $(LLVM_PREFIX)llvm-ar$(LLVM_SUFFIX)
	NM      := $(LLVM_PREFIX)llvm-nm$(LLVM_SUFFIX)
	OBJCOPY := $(LLVM_PREFIX)llvm-objcopy$(LLVM_SUFFIX)
	OBJDUMP := $(LLVM_PREFIX)llvm-objdump$(LLVM_SUFFIX)
	READELF := $(LLVM_PREFIX)llvm-readelf$(LLVM_SUFFIX)
	STRIP   := $(LLVM_PREFIX)llvm-strip$(LLVM_SUFFIX)
else
	CC      := $(CROSS_TOOLCHAIN_PREFIX)gcc
	LD      := $(CROSS_TOOLCHAIN_PREFIX)ld
	AR      := $(CROSS_TOOLCHAIN_PREFIX)ar
	NM      := $(CROSS_TOOLCHAIN_PREFIX)nm
	OBJCOPY := $(CROSS_TOOLCHAIN_PREFIX)objcopy
	OBJDUMP := $(CROSS_TOOLCHAIN_PREFIX)objdump
	READELF := $(CROSS_TOOLCHAIN_PREFIX)readelf
	STRIP   := $(CROSS_TOOLCHAIN_PREFIX)strip
endif

export ARCH SRCARCH
export PREFIX EXEC_PREFIX BOOTDIR LIBDIR INCLUDEDIR
export CROSS_TOOLCHAIN_PREFIX CFLAGS CPPFLAGS SYSROOT CPP
export CC LD AR NM OBJCOPY OBJDUMP READELF STRIP
