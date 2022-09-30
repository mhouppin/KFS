DEFAULT_HOST = $(shell ../default-host.sh)
HOST ?= $(DEFAULT_HOST)
HOSTARCH = $(shell ../target-triplet-to-arch.sh $(HOST))

CFLAGS ?= -O2 -g
CPPFLAGS ?=
LDFLAGS ?=
LIBS ?=

DESTDIR ?=
PREFIX ?= /usr/local
EXEC_PREFIX ?= $(PREFIX)
BOOTDIR ?= $(EXEC_PREFIX)/boot
INCLUDEDIR ?= $(PREFIX)/include

CFLAGS := $(CFLAGS) \
	-ffreestanding -fno-builtin -fno-stack-protector \
	-Wall -Wextra -Wvla -Wshadow

CPPFLAGS := $(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS := $(LDFLAGS)
LIBS := $(LIBS) -nostdlib -nodefaultlibs -lk -lgcc

ARCHDIR = arch/$(HOSTARCH)
include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS := $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS := $(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJECTS = \
	$(KERNEL_ARCH_OBJECTS) \
	utils/kprint_memory.o \
	kernel/kernel.o

OBJECTS = \
	$(ARCHDIR)/crti.o \
	$(ARCHDIR)/crtbegin.o \
	$(KERNEL_OBJECTS) \
	$(ARCHDIR)/crtend.o \
	$(ARCHDIR)/crtn.o

DEPENDS = $(OBJECTS:.o=.d)

LINK_LIST = \
	$(LDFLAGS) \
	$(ARCHDIR)/crti.o \
	$(ARCHDIR)/crtbegin.o \
	$(KERNEL_OBJECTS) \
	$(LIBS) \
	$(ARCHDIR)/crtend.o \
	$(ARCHDIR)/crtn.o

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .s

all: vault.kernel

vault.kernel: $(OBJECTS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld $(CFLAGS) -o $@ $(LINK_LIST)
	grub-file --is-x86-multiboot $@

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

%.o: %.c
	$(CC) -MD -c -o $@ $< -std=gnu11 $(CFLAGS) $(CPPFLAGS)

%.o: %.s
	nasm -g -Fdwarf -D__is_kernel -felf32 -MF $(subst .o,.d,$@) -o $@ $<

clean:
	rm -f vault.kernel
	rm -f $(OBJECTS)
	rm -f $(DEPENDS)

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -pR include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: vault.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp vault.kernel $(DESTDIR)$(BOOTDIR)

-include $(DEPENDS)
