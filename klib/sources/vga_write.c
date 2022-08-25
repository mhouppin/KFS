#include "vga_term.h"

void vga_write(char c)
{
    if (c == '\n')
    {
        _vga_column = 0;
        if (++_vga_row == VGA_HEIGHT)
            _vga_row = 0;
    }
    else if (c == '\r')
    {
        _vga_column = 0;
    }
    else if (c == '\t')
    {
        _vga_column = (_vga_column + 7) & -8;

        if (_vga_column == VGA_WIDTH)
        {
            _vga_column = 0;
            if (++_vga_row == VGA_HEIGHT)
                _vga_row = 0;
        }
    }
    else if (c == '\v')
    {
        if (++_vga_row == VGA_HEIGHT)
            _vga_row = 0;
    }
    else
        vga_write_raw(c);
}
