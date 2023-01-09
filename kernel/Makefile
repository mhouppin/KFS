NAME := libcpt.a

kernel_CFLAGS := $(CFLAGS) \
	-ffreestanding -fno-builtin -fno-stack-protector \
	-Wall -Wextra -Wvla -Wshadow -std=gnu11

kernel_ASFLAGS := -D__is_kernel
kernel_CPPFLAGS := $(CPPFLAGS) -I include -D__is_kernel
kernel_LDFLAGS := $(LDFLAGS)

kernel_OBJECTS := kernel_main.o

include arch/$(SRCARCH)/common/config.mk
include arch/$(SRCARCH)/$(SUBARCH)/config.mk

kernel_DEPENDS := $(kernel_OBJECTS:.o=.d)

all: $(NAME)

$(NAME): $(kernel_OBJECTS)
	$(AR) -rc  $@ $^

%.o: %.c
	$(CC) -MD -c  -o $@ $< $(CFLAGS) $(CPPFLAGS)

%.o: %.s
	$(CC) $(kernel_ASFLAGS) -c -o $@ $<

clean:
	rm -f $(NAME)
	rm -f $(kernel_OBJECTS)
	rm -f $(kernel_DEPENDS)

-include $(kernel_DEPENDS)
