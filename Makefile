NAME := segv.iso

CC := i686-elf-gcc

SEGV_BIN := isodir/boot/segv.bin
SEGV_GRUB_CFG := isodir/boot/grub/grub.cfg

SEGV_ISO_SOURCES := $(SEGV_BIN)

KLIB_C_SOURCES := \
	klib/sources/kmemccpy.c \
	klib/sources/kmemchr.c \
	klib/sources/kmemcmp.c \
	klib/sources/kmemcpy.c \
	klib/sources/kmemmove.c \
	klib/sources/kmemset.c \
	klib/sources/kstrcat.c \
	klib/sources/kstrchr.c \
	klib/sources/kstrchrnul.c \
	klib/sources/kstrcpy.c \
	klib/sources/kstrlcat.c \
	klib/sources/kstrlen.c \
	klib/sources/kstrncat.c \
	klib/sources/kstrncpy.c \
	klib/sources/kstrnlen.c \
	klib/sources/kstrrchr.c \
	klib/sources/vga_init.c \
	klib/sources/vga_setcolor.c \
	klib/sources/vga_write.c \
	klib/sources/vga_write_raw.c \
	klib/sources/vga_write_raw_pos.c \
	klib/sources/vga_writebuf.c \
	klib/sources/vga_writestr.c

SEGV_BIN_C_SOURCES := bootstrap/kernel.c $(KLIB_C_SOURCES)
SEGV_BIN_ASM_SOURCES := bootstrap/boot.s

SEGV_BIN_OBJECTS := $(SEGV_BIN_C_SOURCES:%.c=%.o)
SEGV_BIN_OBJECTS += $(SEGV_BIN_ASM_SOURCES:%.s=%.o)

SEGV_BIN_DEPENDS := $(SEGV_BIN_OBJECTS:%.o=%.d)

all: $(NAME)

$(NAME): $(SEGV_BIN) $(SEGV_GRUB_CFG)
	grub-mkrescue -o $@ isodir

$(SEGV_BIN): $(SEGV_BIN_OBJECTS)
	mkdir -p $(dir $@)
	$(CC) -T bootstrap/linker.ld -o $@ \
		-ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs \
		-O2 -m32 $^ -lgcc

$(SEGV_GRUB_CFG):
	mkdir -p $(dir $@)
	echo "menuentry \"segv\" {\n    multiboot /boot/segv.bin\n}" > $@

%.o: %.c
	$(CC) -Wall -Wextra -Wvla -Wshadow -Werror \
		-ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs \
		-O2 -m32 -std=gnu99 -c -MMD -I klib/include -o $@ $<

%.o: %.s
	nasm -felf32 -MF $(subst .o,.d,$@) -o $@ $<

-include $(SEGV_BIN_DEPENDS)

clean:
	rm -rf isodir
	rm -f $(SEGV_BIN_OBJECTS)
	rm -f $(SEGV_BIN_DEPENDS)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	+$(MAKE) all

.PHONY: all clean fclean re
