#include "gdt.h"

void segment_desc_set(struct gdt_segment_desc *desc,
    uint32_t base, uint32_t limit, uint8_t flags, uint8_t access_byte)
{
    desc->buffer[0] = (uint8_t)limit;
    desc->buffer[1] = (uint8_t)(limit >> 8);
    desc->buffer[2] = (uint8_t)base;
    desc->buffer[3] = (uint8_t)(base >> 8);
    desc->buffer[4] = (uint8_t)(base >> 16);
    desc->buffer[5] = access_byte;
    desc->buffer[6] = (uint8_t)((limit >> 16) & 0xFu) | (flags << 4);
    desc->buffer[7] = (uint8_t)(base >> 24);
}
