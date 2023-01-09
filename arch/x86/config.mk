# Determine if we're building for 64-bit or 32-bit x86.
ifeq ($(ARCH),x86)
	ifeq ($(shell uname -m),x86_64)
		SUBARCH := x86_64
	else
		SUBARCH := i386
	endif
else
	SUBARCH := $(ARCH)
endif

# Work around that the -elf gcc targets don't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
ifneq ($(shell echo $(CROSS_TOOLCHAIN_PREFIX) | grep -E -- '-elf($$|-)'),)
	CFLAGS += -isystem=$(INCLUDEDIR)
else
	CFLAGS += --sysroot=$(SYSROOT)
endif

GRUB_MULTIBOOT_CHECK := grub-file --is-x86-multiboot

export SUBARCH
