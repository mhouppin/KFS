#include "vga_term.h"
 
void vga_write_raw_pos(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	_vga_buffer[index] = vga_entry(c, color);
}
