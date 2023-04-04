#ifndef _KERNEL_VGA_TTY_H
#define _KERNEL_VGA_TTY_H 1

#include <stddef.h>
#include <stdint.h>

// Hardware text mode color constants.
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

void vga_init(void);
void vga_setcolor(uint8_t color);
void vga_write_raw_pos(char c, uint8_t color, size_t x, size_t y);
void vga_write_raw(char c);
void vga_write(char c);
void vga_writebuf(const void *buf, size_t size);
void vga_writestr(const char *data);

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

#endif
