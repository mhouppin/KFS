#include <stdio.h>

#ifdef __is_libk
#include <kernel/vga_tty.h>
#endif

int putchar(int c)
{
#ifdef __is_libk
    char b = (char)c;

    vga_write(b);
#else
    // TODO: Implement stdio and the write syscall.
#endif
    return c;
}
