#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga_tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

static size_t _vga_row;
static size_t _vga_column;
static uint8_t _vga_color;
static uint16_t *_vga_buffer;

void vga_init(void)
{
	_vga_row = 0;
	_vga_column = 0;
	_vga_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	_vga_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			_vga_buffer[index] = vga_entry(' ', _vga_color);
		}
	}
}
 
void vga_setcolor(uint8_t color) 
{
	_vga_color = color;
}

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

void vga_write_raw(char c)
{
	vga_write_raw_pos(c, _vga_color, _vga_column, _vga_row);
	if (++_vga_column == VGA_WIDTH) {
		_vga_column = 0;
		if (++_vga_row == VGA_HEIGHT)
			_vga_row = 0;
	}
}
 
void vga_write_raw_pos(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	_vga_buffer[index] = vga_entry(c, color);
}
 
void vga_writebuf(const void* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		vga_write(((const char *)data)[i]);
}

void vga_writestr(const char* data) 
{
    vga_writebuf(data, strlen(data));
}
