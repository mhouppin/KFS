#include <kernel/utils.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void kprint_leading_addr(uintptr_t addr)
{
    unsigned char buffer[11];

    buffer[0] = '0';
    buffer[1] = 'x';
    buffer[10] = '\0';

    for (int h = 0; h < 8; ++h)
    {
        uint8_t value = addr & 0xFu;

        buffer[9 - h] = (value < 10) ? value + '0' : value + 'a' - 10;
        addr >>= 4;
    }

    printf("%s ", (char *)buffer);
}

static void kprint_range(uintptr_t addr, size_t start, size_t end)
{
    unsigned char buffer[57];

    memset(buffer, ' ', sizeof(buffer));
    buffer[56] = '\0';

    for (size_t i = start; i < end; ++i)
    {
        size_t hex_offset = i * 2 + (i / 2);
        size_t byte_offset = i + 40;

        uint8_t value = *(const uint8_t *)(addr + i);
        uint8_t hi4 = value >> 4;
        uint8_t lo4 = value & 0xFu;

        buffer[hex_offset + 0] = (hi4 < 10) ? hi4 + '0' : hi4 + 'a' - 10;
        buffer[hex_offset + 1] = (lo4 < 10) ? lo4 + '0' : lo4 + 'a' - 10;
        buffer[byte_offset] = (value >= 32 && value <= 127) ? value : '.';
    }

    printf("%s\n", (char *)buffer);
}

void kprint_memory(const void *addr, size_t size)
{
    uintptr_t ptr = (uintptr_t)addr;
    uintptr_t align = ptr & ~(uintptr_t)0xFu;

    kprint_leading_addr(align);

    if (ptr + size < align + 16)
    {
        kprint_range(align, ptr - align, ptr + size - align);
        return ;
    }

    kprint_range(align, ptr - align, 16);
    size -= 16 - (ptr - align);
    ptr = align + 16;

    while (size)
    {
        kprint_leading_addr(ptr);

        size_t end = (size > 16) ? 16 : size;

        kprint_range(ptr, 0, end);
        ptr += 16;
        size -= end;
    }
}
