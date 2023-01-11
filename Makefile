include config.mk

NAME := cpt.kernel
ISONAME := cpt.iso

cpt_CFLAGS := $(CFLAGS) \
	-ffreestanding -fno-builtin -fno-stack-protector \
	-Wall -Wextra -Wvla -Wshadow

cpt_LINKER_SCRIPT := arch/$(SRC_ARCH)/$(SRC_SUBARCH)/boot/linker.ld

cpt_LDFLAGS := $(LDFLAGS) -T $(cpt_LINKER_SCRIPT) -nostdlib -nodefaultlibs -lgcc

include arch/$(SRC_ARCH)/$(SRC_SUBARCH)/boot/config.mk

cpt_CFLAGS += $(boot_CFLAGS)
cpt_CPPFLAGS += $(boot_CPPFLAGS)
cpt_LDFLAGS += $(boot_LDFLAGS)
cpt_OBJECTS += $(boot_OBJECTS)

all: $(NAME)

# TODO: add support for clang linker configuration

$(NAME): kernel/libkernel.a $(cpt_LINKER_SCRIPT) $(cpt_OBJECTS)
	$(CC) $(cpt_CFLAGS) -o $@ $(cpt_OBJECTS) kernel/libkernel.a $(cpt_LDFLAGS)
	$(GRUB_MULTIBOOT_CHECK) $@ || rm -f $@

%.o: %.s
	$(CC) $(cpt_ASFLAGS) -c -o $@ $<

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
	$(MAKE) clean -C kernel

FORCE:

.PHONY: all iso clean
