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
};

// Port output functions
void port_out_u8(uint16_t port, uint8_t data);
void port_out_u16(uint16_t port, uint16_t data);
void port_out_u32(uint16_t port, uint32_t data);

// Port input functions
uint8_t port_in_u8(uint16_t port);
uint16_t port_in_u16(uint16_t port);
uint32_t port_in_u32(uint16_t port);

#endif