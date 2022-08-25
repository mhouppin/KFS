NAME := vault.iso

CC := i686-elf-gcc

VAULT_BIN := isodir/boot/vault.bin
VAULT_GRUB_CFG := isodir/boot/grub/grub.cfg

VAULT_ISO_SOURCES := $(VAULT_BIN)

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

VAULT_BIN_C_SOURCES := bootstrap/kernel.c $(KLIB_C_SOURCES)
VAULT_BIN_ASM_SOURCES := bootstrap/boot.s

VAULT_BIN_OBJECTS := $(VAULT_BIN_C_SOURCES:%.c=%.o)
VAULT_BIN_OBJECTS += $(VAULT_BIN_ASM_SOURCES:%.s=%.o)

VAULT_BIN_DEPENDS := $(VAULT_BIN_OBJECTS:%.o=%.d)

all: $(NAME)

$(NAME): $(VAULT_BIN) $(VAULT_GRUB_CFG)
	grub-mkrescue -o $@ isodir

$(VAULT_BIN): $(VAULT_BIN_OBJECTS)
	mkdir -p $(dir $@)
	$(CC) -T bootstrap/linker.ld -o $@ \
		-ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs \
		-O2 -m32 $^ -lgcc

$(VAULT_GRUB_CFG):
	mkdir -p $(dir $@)
	echo "menuentry \"vault\" {\n    multiboot /boot/vault.bin\n}" > $@

%.o: %.c
	$(CC) -Wall -Wextra -Wvla -Wshadow -Werror \
		-ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs \
		-O2 -m32 -std=gnu99 -c -MMD -I klib/include -o $@ $<

%.o: %.s
	nasm -felf32 -MF $(subst .o,.d,$@) -o $@ $<

-include $(VAULT_BIN_DEPENDS)

clean:
	rm -rf isodir
	rm -f $(VAULT_BIN_OBJECTS)
	rm -f $(VAULT_BIN_DEPENDS)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	+$(MAKE) all

.PHONY: all clean fclean re
