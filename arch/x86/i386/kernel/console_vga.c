#include "terminal_vga.h"
#include "string.h"
#include "port.h"

const unsigned void *console_vga_buffer = (void *)VGA_BUFFER_ADDRESS;

console_vga_context_t console_context;

void console_vga_register(current_driver_t *current_driver)
{
    // Register the driver
    current_driver->console_init = &console_vga_init;
    current_driver->console_destroy = &console_vga_destroy;

    current_driver->console_write_char = console_vga_write_char;
    current_driver->console_write_string = console_vga_write_string;

    current_driver->console_clear = console_vga_clear;
    current_driver->console_scroll = console_vga_scroll;

}

void console_vga_init()
{
    // Set default terminal size
    console_context.columns = VGA_COLUMNS;
    console_context.rows = VGA_ROWS;

    // Set default cursor position
    console_context.cursor_x = 0;
    console_context.cursor_y = 0;

    // Set default style
    console_context.style.font_color = VGA_COLOR_WHITE;
    console_context.style.background_color = VGA_COLOR_BLACK;
}

void console_vga_destroy()
{
    // Nothing to do
}

void console_vga_write_char(const char c)
{
    // Process all special characters
    
    // New line
    if (c == '\n')
    {
        console_context.cursor_x = 0;

        if (console_context.cursor_y < console_context.rows)
            console_context.cursor_y++;
        else
           console_vga_scroll(1);

        return ;
    }
    
    // Carriage return
    if (c == '\r')
    {
        console_context.cursor_x = 0;
        return ;
    }
    
    // Form feed (New Page)
    if (c == '\f')
    {
        // Todo: clear terminal memset(console_vga_buffer, 0, console_context.rows * console_context.columns * sizeof(t_vga_style_format));
        console_context.cursor_x = 0;
        console_context.cursor_y = 0;
        return ;
    }
    
    // Backspace
    if (c == '\b')
    {
        if (console_context.cursor_x > 0)
            console_context.cursor_x--;
        return ;
    }
    
    // Horizontal tab
    if (c == '\t')
    {
        console_context.cursor_x += 4 - (console_context.cursor_x % 4);
        if (console_context.cursor_x >= console_context.columns)
        {
            console_context.cursor_x = console_context.cursor_x - console_context.columns;
            console_context.cursor_y++;
        }
        return ;
    }
    
    // Vertical tab
    if (c == '\v')
    {
        console_context.cursor_y++;
        if (console_context.cursor_y >= console_context.rows)
            console_vga_scroll(1);
        return ;
    }

    unsigned int position = console_context.cursor_y * console_context.columns + console_context.cursor_x;

    console_vga_buffer[position].character = c;
    console_vga_buffer[position].font_color = console_context.style.font_color;
    console_vga_buffer[position].background_color = console_context.style.background_color;

    console_context.cursor_x++;

    if (console_context.cursor_x >= console_context.columns)
    {
        console_context.cursor_x = 0;
        console_context.cursor_y++;

        if (console_context.cursor_y >= console_context.rows)
            console_vga_scroll(1);
    }
}

void console_vga_write_string(const char *string)
{
    while (*string)
        console_vga_write_char(*string++);
    console_vga_cursor_update();
}

void console_vga_write(const char *string, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        console_vga_write_char(string[i]);
}

void console_vga_scroll(unsigned int lines)
{
    if (lines > console_context.rows)
        lines = console_context.rows;
    
    memmove(console_vga_buffer, console_vga_buffer + (lines * console_context.columns),
    (console_context.rows - lines) * console_context.columns * sizeof(t_vga_style_format));
    memset(console_vga_buffer + ((console_context.rows - lines) * console_context.columns), 0, lines * console_context.columns * sizeof(t_vga_style_format));
}

// -----------------------------------------------------------------------------------------------

void console_vga_cursor_enable()
{
    port_out_byte(VGA_PORT_COMMAND, VGA_COMMAND_CURSOR_START);
    port_out_byte(VGA_PORT_DATA, (port_int_byte(VGA_PORT_DATA) & 0xC0) | 0x0E); // 0x0E = 14 = 1110

    port_out_byte(VGA_PORT_COMMAND, VGA_COMMAND_TEXT_CURSOR_END);
    port_out_byte(VGA_PORT_DATA, (port_int_byte(VGA_PORT_DATA) & 0xE0) | 0x0F); // 0x0F = 15 = 1111
}

void console_vga_cursor_disable()
{
    port_out_byte(VGA_PORT_COMMAND, VGA_COMMAND_CURSOR_START);
    port_out_byte(VGA_PORT_DATA, 0x20); // 0x20 = 32 = 0010 0000 Disable cursor
}

console_vga_cursor_move(size_t x, size_t y)
{
    if (x >= console_context.columns)
        x = console_context.columns - 1;
    if (y >= console_context.rows)
        y = console_context.rows - 1;

    console_context.cursor_x = x;
    console_context.cursor_y = y;
    console_vga_cursor_update();
}

//
void console_vga_cursor_update()
{
    size_t position = console_context.cursor_y * console_context.columns + console_context.cursor_x;

    // Send cursor location to VGA controller the coordinates are 16 bits but we send them as 2 bytes
    port_out_byte(VGA_PORT_COMMAND, VGA_COMMAND_CURSOR_LOCATION_LOW);
    port_out_byte(VGA_PORT_DATA, (unsigned char)(position & 0xFF));

    port_out_byte(VGA_PORT_COMMAND, VGA_COMMAND_CURSOR_LOCATION_HIGH);
    port_out_byte(VGA_PORT_DATA, (unsigned char)((position >> 8) & 0xFF));
}
