#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga_tty.h>

#include "vga.h"
#include "port.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

static size_t _vga_row;
static size_t _vga_column;
static uint8_t _vga_color;
static uint16_t *_vga_buffer;

#define VGA_DEFAULT_COLOR vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK)

void vga_init(void)
{
    _vga_row = 0;
    _vga_column = 0;
    _vga_color = VGA_DEFAULT_COLOR;
    _vga_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            _vga_buffer[index] = vga_entry(' ', _vga_color);
        }
    }
    vga_cursor_enable();
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
            vga_scroll();
    }
    else if (c == '\r')
    {
        _vga_column = 0;
    }
    else if (c == '\t')
    {
        _vga_column += 8 - (_vga_column % 8);

        if (_vga_column >= VGA_WIDTH)
        {
            _vga_column = 0;
            if (++_vga_row == VGA_HEIGHT)
                vga_scroll();
        }
    }
    else if (c == '\b')
    {
        if (_vga_column > 0)
            _vga_column--;
        else if (_vga_row > 0)
        {
            _vga_column = VGA_WIDTH - 1;
            _vga_row--;
        }
    }
    else if (c == '\f')
    {
        _vga_column = 0;
        _vga_row = 0;
        memset(
                _vga_buffer,
                0,
                VGA_WIDTH * VGA_HEIGHT * sizeof(uint16_t)
              );
    }
    else if (c == '\v')
    {
        if (++_vga_row == VGA_HEIGHT)
            vga_scroll();
    }
    else
        vga_write_raw(c);
    vga_cursor_update();
}

void vga_scroll()
{
    if (_vga_row > 0)
        _vga_row--;
    memcpy(_vga_buffer, _vga_buffer + VGA_WIDTH, VGA_WIDTH * (VGA_HEIGHT - 1) * sizeof(uint16_t));
    memset(
            _vga_buffer + VGA_WIDTH * (VGA_HEIGHT - 1),
            0,
            VGA_WIDTH * sizeof(uint16_t)
          );
}

void vga_write_raw(char c)
{
    vga_write_raw_pos(c, _vga_color, _vga_column, _vga_row);
    if (++_vga_column == VGA_WIDTH) {
        _vga_column = 0;
        if (++_vga_row == VGA_HEIGHT)
            vga_scroll();
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

void vga_cursor_enable()
{
    port_out_u8(VGA_PORT_COMMAND, VGA_COMMAND_TEXT_CURSOR_START);
    port_out_u8(VGA_PORT_DATA, (port_in_u8(VGA_PORT_DATA) & 0xC0) | 0x0E); // 0x0E = 14 = 1110

    port_out_u8(VGA_PORT_COMMAND, VGA_COMMAND_TEXT_CURSOR_END);
    port_out_u8(VGA_PORT_DATA, (port_in_u8(VGA_PORT_DATA) & 0xE0) | 0x0F); // 0x0F = 15 = 1111
}

void vga_cursor_disable()
{
    port_out_u8(VGA_PORT_COMMAND, VGA_COMMAND_TEXT_CURSOR_START);
    port_out_u8(VGA_PORT_DATA, 0x20); // 0x20 = 32 = 0010 0000 Disable cursor
}

void vga_cursor_update()
{
    size_t position = _vga_row * VGA_WIDTH + _vga_column;

    // Send cursor location to VGA controller the coordinates are 16 bits but we send them as one bytes at a time.
    port_out_u8(VGA_PORT_COMMAND, VGA_COMMAND_TEXT_CURSOR_LOCATION_LOW);
    port_out_u8(VGA_PORT_DATA, (unsigned char)(position & 0xFF));

    port_out_u8(VGA_PORT_COMMAND, VGA_COMMAND_TEXT_CURSOR_LOCATION_HIGH);
    port_out_u8(VGA_PORT_DATA, (unsigned char)((position >> 8) & 0xFF));
}
