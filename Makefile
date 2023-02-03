include config.mk

NAME := cpt.kernel
ISONAME := cpt.iso

cpt_CFLAGS := $(CFLAGS) \
	-ffreestanding -fno-builtin -fno-stack-protector \
	-Wall -Wextra -Wvla -Wshadow

cpt_LINKER_SCRIPT := boot/arch/$(SRC_ARCH)/linker.ld

cpt_LDFLAGS := $(LDFLAGS) -T $(cpt_LINKER_SCRIPT) -nostdlib -nodefaultlibs # -lgcc

cpt_STATICLIBS := boot/libcpt_boot.a kernel/libkernel.a

include boot/arch/$(SRC_ARCH)/config.mk

all: $(NAME)

# TODO: add support for clang linker configuration

$(NAME): $(cpt_STATICLIBS) $(cpt_LINKER_SCRIPT)
	$(CC) $(cpt_CFLAGS) -o $@ $(cpt_STATICLIBS) $(cpt_LDFLAGS)
	$(GRUB_MULTIBOOT_CHECK) $@ || rm -f $@

boot/libcpt_boot.a: FORCE
	$(MAKE) -C boot

kernel/libkernel.a: FORCE
	$(MAKE) -C kernel

iso: $(ISONAME)

$(ISONAME): $(NAME)
	mkdir -p isodir/boot/grub
	cp $(NAME) isodir/boot/$(NAME)
	echo "menuentry \"cpt\" {\n    multiboot /boot/$(NAME)\n}\n" > isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISONAME) isodir

clean:
	rm -f $(NAME)
	rm -f $(cpt_OBJECTS)
	rm -rf isodir
	rm -f $(ISONAME)
	$(MAKE) clean -C boot
	$(MAKE) clean -C kernel

FORCE:

.PHONY: all iso clean
