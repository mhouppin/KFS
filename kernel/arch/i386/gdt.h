#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stdint.h>

#define GDT_ACCESS_ABSENT 0x00u
#define GDT_ACCESS_PRESENT 0x80u

#define GDT_ACCESS_RING_0 0x00u
#define GDT_ACCESS_RING_1 0x20u
#define GDT_ACCESS_RING_2 0x40u
#define GDT_ACCESS_RING_3 0x60u

#define GDT_ACCESS_SYSTEM_SEGM 0x00u
#define GDT_ACCESS_CODE_SEGM 0x10u

#define GDT_ACCESS_NOEXEC 0x00u
#define GDT_ACCESS_EXEC 0x08u

#define GDT_ACCESS_DIR_UP 0x00u
#define GDT_ACCESS_DIR_DOWN 0x04u
#define GDT_ACCESS_EQ_RING 0x00u
#define GDT_ACCESS_LE_RING 0x04u

#define GDT_ACCESS_READABLE 0x02u
#define GDT_ACCESS_WRITEABLE 0x02u

#define GDT_ACCESS_ACCBIT 0x01u

#define GDT_FLAG_BYTE_GRANULAR 0x00u
#define GDT_FLAG_PAGE_GRANULAR 0x08u

#define GDT_FLAG_16BIT_SEGM 0x00u
#define GDT_FLAG_32BIT_SEGM 0x04u

#define GDT_FLAG_NO_LONG_MODE 0x00u
#define GDT_FLAG_LONG_MODE 0x02u

#define GDT_FLAG_RESERVED 0x01u

struct gdt_segment_desc {
    uint8_t buffer[8];
};

void segment_desc_set(struct gdt_segment_desc *desc,
    uint32_t base, uint32_t limit, uint8_t flags, uint8_t access_byte);

void gdt_configure(struct gdt_segment_desc *base, uint16_t limit);

#endif
