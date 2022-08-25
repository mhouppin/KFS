#include "vga_term.h"

void vga_write_raw(char c)
{
	vga_write_raw_pos(c, _vga_color, _vga_column, _vga_row);
	if (++_vga_column == VGA_WIDTH) {
		_vga_column = 0;
		if (++_vga_row == VGA_HEIGHT)
			_vga_row = 0;
	}
}
