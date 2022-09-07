#ifndef _KERNEL_VGA_TTY_H
#define _KERNEL_VGA_TTY_H 1

#include <stddef.h>
#include <stdint.h>

void vga_init(void);
void vga_setcolor(uint8_t color);
void vga_write_raw_pos(char c, uint8_t color, size_t x, size_t y);
void vga_write_raw(char c);
void vga_write(char c);
void vga_writebuf(const void *buf, size_t size);
void vga_writestr(const char *data);

#endif
