#ifndef _ARCH_I386_VGA_H
#define _ARCH_I386_VGA_H 1
 
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

// VGA command port
enum e_vga_port
{
    VGA_PORT_COMMAND = 0x3D4,
    VGA_PORT_DATA = 0x3D5,
};

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

void vga_cursor_enable();
void vga_cursor_disable();
void vga_cursor_update();
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}
 
#endif
