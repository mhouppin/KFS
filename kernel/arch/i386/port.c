#include "port.h"
// Generic port specific functions

// Port I/O functions
// These are used to access the I/O ports on the x86 architecture
// They are used to access the VGA text buffer and the keyboard
//

// Read a byte from the specified port
uint8_t port_in_u8(uint16_t port)
{
    uint8_t result;
    __asm__ volatile("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

uint16_t port_in_u16(uint16_t port)
{
    uint16_t result;
    __asm__ volatile("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

uint32_t port_in_u32(uint16_t port)
{
    uint32_t result;
    __asm__ volatile("in %%dx, %%eax" : "=a" (result) : "d" (port));
    return result;
}

// Write a byte to the specified port
void port_out_u8(uint16_t port, uint8_t data)
{
    __asm__ volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}

void port_out_u16(uint16_t port, uint16_t data)
{
    __asm__ volatile("out %%ax, %%dx" : : "a" (data), "d" (port));
}

void port_out_u32(uint16_t port, uint32_t data)
{
    __asm__ volatile("out %%eax, %%dx" : : "a" (data), "d" (port));
}