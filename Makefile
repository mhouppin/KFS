include config.mk

NAME := cpt.bin

cpt_CFLAGS := $(CFLAGS) \
	-ffreestanding -fno-builtin -fno-stack-protector \
	-Wall -Wextra -Wvla -Wshadow

cpt_LDFLAGS := $(LDFLAGS) -T arch/$(SRCARCH)/linker.ld -nostdlib -nodefaultlibs -lgcc

all: $(NAME)

# TODO: add support for clang linker configuration

$(NAME): kernel/libcpt.a arch/$(SRCARCH)/linker.ld #libc/libk.a
	$(CC) $(cpt_CFLAGS) -o $@ kernel/libcpt.a $(cpt_LDFLAGS)
	$(GRUB_MULTIBOOT_CHECK) $@ || rm -f $@

kernel/libcpt.a: FORCE
	$(MAKE) -C kernel

#libc/libk.a: FORCE
#	$(MAKE) -C libc

clean:
	rm -f $(NAME)
	$(MAKE) clean -C kernel

FORCE:
