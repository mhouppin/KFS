#ifndef PORT_H
#define PORT_H

#include <stdint.h>

// Port Identifiers
enum e_port_id
{
    PORT_ID_COM1 = 0x3F8,
    PORT_ID_COM2 = 0x2F8,
    PORT_ID_COM3 = 0x3E8,
    PORT_ID_COM4 = 0x2E8,
    PORT_ID_LPT1 = 0x3BC,
    PORT_ID_LPT2 = 0x378,
    PORT_ID_LPT3 = 0x278,
    PORT_ID_KEYBOARD = 0x60,
    PORT_ID_KEYBOARD_STATUS = 0x64,
    PORT_ID_KEYBOARD_COMMAND = 0x64,
    PORT_ID_KEYBOARD_DATA = 0x60,
    PORT_ID_KEYBOARD_CONTROL = 0x64,
    PORT_ID_KEYBOARD_TEST = 0x64,
    PORT_ID_KEYBOARD_SELF_TEST = 0x60,
    PORT_ID_KEYBOARD_INTERFACE_TEST = 0x60,
    PORT_ID_KEYBOARD_DISABLE = 0x60,
    PORT_ID_KEYBOARD_ENABLE = 0x60,
    PORT_ID_KEYBOARD_READ = 0x60,
    PORT_ID_KEYBOARD_WRITE = 0x60,
    PORT_ID_KEYBOARD_WRITE_OUTPUT = 0x60,
    PORT_ID_KEYBOARD_WRITE_INPUT = 0x60,
    PORT_ID_KEYBOARD_WRITE_TEST = 0x60,
    PORT_ID_KEYBOARD_WRITE_TEST_INPUT = 0x60,
    PORT_ID_KEYBOARD_WRITE_TEST_OUTPUT = 0x60,
    PORT_ID_KEYBOARD_WRITE_DISABLE = 0x60,
    PORT_ID_KEYBOARD_WRITE_ENABLE = 0x60,
    PORT_ID_KEYBOARD_WRITE_READ = 0x60,

};

// Port output functions
void port_out_u8(uint16_t port, uint8_t data);
void port_out_u16(uint16_t port, uint16_t data);
void port_out_u32(uint16_t port, uint32_t data);

// Port input functions
uint8_t port_int_u8(uint16_t port);
uint8_t port_int_u16(uint16_t port);
uint8_t port_int_u32(uint16_t port);

#endif