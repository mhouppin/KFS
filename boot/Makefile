NAME := libcpt_boot.a

boot_CFLAGS := $(CFLAGS) \
	-ffreestanding -fno-builtin -fno-stack-protector \
	-Wall -Wextra -Wvla -Wshadow -std=gnu11

boot_ASFLAGS := $(ASFLAGS)
boot_CPPFLAGS := $(CPPFLAGS)
boot_LDFLAGS := $(LDFLAGS)

boot_OBJECTS :=

include arch/$(SRC_ARCH)/config.mk

boot_DEPENDS := $(boot_OBJECTS:.o=.d)

all: $(NAME)

$(NAME): $(boot_OBJECTS)
	$(AR) -rcs $@ $^

%.o: %.c
	$(CC) -MD -c -o $@ $< $(boot_CFLAGS) $(boot_CPPFLAGS)

%.o: %.s
	$(CC) $(boot_ASFLAGS) -c -o $@ $<

clean:
	rm -f $(NAME)
	rm -f $(boot_OBJECTS)
	rm -f $(boot_DEPENDS)

-include $(boot_DEPENDS)

.PHONY: all clean
