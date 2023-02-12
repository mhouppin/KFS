#ifndef CONSOLE_VGA_H
#define CONSOLE_VGA_H

/**
 * @file console_vga.h
 * @brief This file contains the VGA Mode text console driver.
*/

#include "console.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_BUFFER_ADDRESS 0xB8000
#define VGA_BUFFER_SIZE (VGA_WIDTH * VGA_HEIGHT * 2)

// VGA COLORS
enum e_vga_color
{
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

// VGA PORTS
enum e_vga_port
{
    VGA_PORT_COMMAND = 0x3D4,
    VGA_PORT_DATA = 0x3D5,
};

// VGA COMMANDS
enum e_vga_command
{
    VGA_COMMAND_HORIZONTAL_TOTAL = 0x00,
    VGA_COMMAND_HORIZONTAL_DISPLAY_END = 0x01,
    VGA_COMMAND_HORIZONTAL_BLANKING_START = 0x02,
    VGA_COMMAND_HORIZONTAL_BLANKING_END = 0x03,
    VGA_COMMAND_HORIZONTAL_SYNC_START = 0x04,
    VGA_COMMAND_HORIZONTAL_SYNC_END = 0x05,
    VGA_COMMAND_VERTICAL_TOTAL = 0x06,
    VGA_COMMAND_OVERFLOW = 0x07,
    VGA_COMMAND_PRESET_ROW_SCAN = 0x08,
    VGA_COMMAND_MAXIMUM_SCAN_LINE = 0x09,
    VGA_COMMAND_TEXT_CURSOR_START = 0x0A,
    VGA_COMMAND_TEXT_CURSOR_END = 0x0B,
    VGA_COMMAND_START_ADDRESS_HIGH = 0x0C,
    VGA_COMMAND_START_ADDRESS_LOW = 0x0D,
    VGA_COMMAND_TEXT_CURSOR_LOCATION_HIGH = 0x0E,
    VGA_COMMAND_TEXT_CURSOR_LOCATION_LOW = 0x0F,
    VGA_COMMAND_VERTICAL_SYNC_START = 0x10,
    VGA_COMMAND_VERTICAL_SYNC_END = 0x11,
    VGA_COMMAND_VERTICAL_DISPLAY_END = 0x12,
    VGA_COMMAND_OFFSET = 0x13,
    VGA_COMMAND_UNDERLINE_LOCATION = 0x14,
    VGA_COMMAND_VERTICAL_BLANKING_START = 0x15,
    VGA_COMMAND_VERTICAL_BLANKING_END = 0x16,
    VGA_COMMAND_MODE_CONTROL = 0x17,
    VGA_COMMAND_LINE_COMPARE = 0x18,
    VGA_COMMAND_MEMORY_READ_LATCH_DATA = 0x22,
    VGA_COMMAND_TOGGLE_STATE_OF_ATTRIBUTE_CONTROLLER = 0x24,
};

// This structure contains one char with this color style.
struct console_vga_character
{
    char character;
    unsigned char font_color : 4;
    unsigned char background_color : 4;
};

typedef struct vga_character console_vga_character_t;

struct console_vga_context
{
    unsigned int columns;
    unsigned int rows;

    unsigned int cursor_x;
    unsigned int cursor_y;
    unsigned char font_color : 4;
    unsigned char background_color : 4;
};

typedef struct console_vga_context console_vga_context_t;

void console_vga_register();
void console_vga_init();
void console_vga_destroy();

void console_vga_set_color(unsigned char font_color, unsigned char background_color);

void console_vga_write_char(char character);
void console_vga_write_string(char *string);
// void console_vga_write(void *string, unsigned int size);

void console_vga_scroll(unsigned int lines);

#endif