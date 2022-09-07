DEFAULT_HOST != ../default-host.sh
HOST ?= DEFAULT_HOST
HOSTARCH != ../target-triplet-to-arch.sh $(HOST)

CFLAGS ?= -O2 -g
CPPFLAGS ?=
LDFLAGS ?=
LIBS ?=

DESTDIR ?=
PREFIX ?= /usr/local
EXEC_PREFIX ?= $(PREFIX)
INCLUDEDIR ?= $(PREFIX)/include
LIBDIR ?= $(EXEC_PREFIX)/lib

CFLAGS := $(CFLAGS) \
	-ffreestanding -fno-builtin -fno-stack-protector \
	-Wall -Wextra -Wvla -Wshadow

CPPFLAGS := $(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CFLAGS := $(CFLAGS)
LIBK_CPPFLAGS := $(CPPFLAGS) -D__is_libk

ARCHDIR = arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS := $(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS := $(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREE_OBJECTS = \
	$(ARCH_FREE_OBJECTS) \
	stdio/printf.o \
	stdio/putchar.o \
	stdio/puts.o \
	stdlib/abort.o \
	string/memccpy.o \
	string/memchr.o \
	string/memcmp.o \
	string/memcpy.o \
	string/memmove.o \
	string/memset.o \
	string/strcat.o \
	string/strchr.o \
	string/strchrnul.o \
	string/strcpy.o \
	string/strlcat.o \
	string/strlen.o \
	string/strncat.o \
	string/strncpy.o \
	string/strnlen.o \
	string/strrchr.o

HOSTED_OBJECTS = \
	$(ARCH_HOSTED_OBJECTS)

OBJECTS = \
	$(FREE_OBJECTS) \
	$(HOSTED_OBJECTS)

LIBK_OBJECTS = $(FREE_OBJECTS:.o=.libk.o)

DEPENDS = \
	$(OBJECTS:.o=.d) \
	$(LIBK_OBJECTS:.o=.d)

# TODO: add libc to the binaries later
BINARIES = libk.a # libc.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .s

all: $(BINARIES)

libc.a: $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)

libk.a: $(LIBK_OBJECTS)
	$(AR) rcs $@ $(LIBK_OBJECTS)

%.o: %.c
	$(CC) -MD -c -o $@ $< -std=gnu11 $(CFLAGS) $(CPPFLAGS)

%.o: %.s
	nasm -D__is_libc -felf32 -MF $(subst .o,.d,$@) -o $@ $<

%.libk.o: %.c
	$(CC) -MD -c -o $@ $< -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

%.libk.o: %.s
	nasm -D__is_libc -D__is_libk -felf32 -MF $(subst .o,.d,$@) -o $@ $<

clean:
	rm -f $(BINARIES)
	rm -f $(OBJECTS) $(LIBK_OBJECTS)
	rm -f $(DEPENDS)

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(DEPENDS)
