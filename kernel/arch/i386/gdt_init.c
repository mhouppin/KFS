#include "gdt.h"

void gdt_init(void)
{
    struct gdt_segment_desc *segments = (struct gdt_segment_desc *)0x800u;

    // Initialize NULL descriptor.
    segment_desc_set(&segments[0],
        0,
        0,
        0,
        0
    );

    // Initialize Kernel Mode Code Segment descriptor.
    segment_desc_set(&segments[1],
        0x00u,
        0xFFFFFu,
        GDT_FLAG_PAGE_GRANULAR
      | GDT_FLAG_32BIT_SEGM
      | GDT_FLAG_NO_LONG_MODE,
        GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING_0
      | GDT_ACCESS_CODE_SEGM
      | GDT_ACCESS_EXEC
      | GDT_ACCESS_EQ_RING
      | GDT_ACCESS_READABLE
    );

    // Initialize Kernel Mode Data Segment descriptor.
    segment_desc_set(&segments[2],
        0x00u,
        0xFFFFFu,
        GDT_FLAG_PAGE_GRANULAR
      | GDT_FLAG_32BIT_SEGM
      | GDT_FLAG_NO_LONG_MODE,
        GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING_0
      | GDT_ACCESS_CODE_SEGM
      | GDT_ACCESS_NOEXEC
      | GDT_ACCESS_DIR_UP
    );

    // Initialize Kernel Mode Stack Segment descriptor.
    segment_desc_set(&segments[3],
        0x00u,
        0xFFFFFu,
        GDT_FLAG_PAGE_GRANULAR
      | GDT_FLAG_32BIT_SEGM
      | GDT_FLAG_NO_LONG_MODE,
        GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING_0
      | GDT_ACCESS_CODE_SEGM
      | GDT_ACCESS_NOEXEC
      | GDT_ACCESS_DIR_UP
      | GDT_ACCESS_WRITEABLE
    );

    // Initialize User Mode Code Segment descriptor.
    segment_desc_set(&segments[4],
        0x00u,
        0xFFFFFu,
        GDT_FLAG_PAGE_GRANULAR
      | GDT_FLAG_32BIT_SEGM
      | GDT_FLAG_NO_LONG_MODE,
        GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING_3
      | GDT_ACCESS_CODE_SEGM
      | GDT_ACCESS_EXEC
      | GDT_ACCESS_EQ_RING
      | GDT_ACCESS_READABLE
    );

    // Initialize User Mode Data Segment descriptor.
    segment_desc_set(&segments[5],
        0x00u,
        0xFFFFFu,
        GDT_FLAG_PAGE_GRANULAR
      | GDT_FLAG_32BIT_SEGM
      | GDT_FLAG_NO_LONG_MODE,
        GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING_3
      | GDT_ACCESS_CODE_SEGM
      | GDT_ACCESS_NOEXEC
      | GDT_ACCESS_DIR_UP
    );

    // Initialize User Mode Stack Segment descriptor.
    segment_desc_set(&segments[6],
        0x00u,
        0xFFFFFu,
        GDT_FLAG_PAGE_GRANULAR
      | GDT_FLAG_32BIT_SEGM
      | GDT_FLAG_NO_LONG_MODE,
        GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING_3
      | GDT_ACCESS_CODE_SEGM
      | GDT_ACCESS_NOEXEC
      | GDT_ACCESS_DIR_UP
      | GDT_ACCESS_WRITEABLE
    );

    // Initialize Task State Segment descriptor.
    segment_desc_set(&segments[7],
        0x100000u,
        0x1000u,
        GDT_FLAG_BYTE_GRANULAR
      | GDT_FLAG_16BIT_SEGM
      | GDT_FLAG_NO_LONG_MODE,
        GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING_0
      | GDT_ACCESS_SYSTEM_SEGM
      | GDT_ACCESS_EXEC
      | GDT_ACCESS_EQ_RING
      | GDT_ACCESS_ACCBIT
    );

    gdt_configure(segments, 8);
}
