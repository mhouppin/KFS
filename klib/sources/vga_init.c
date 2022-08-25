#include "vga_term.h"

size_t _vga_row;
size_t _vga_column;
uint8_t _vga_color;
uint16_t *_vga_buffer;

void vga_init(void)
{
	_vga_row = 0;
	_vga_column = 0;
	_vga_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	_vga_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			_vga_buffer[index] = vga_entry(' ', _vga_color);
		}
	}
}
