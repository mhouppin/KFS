#include <stdint.h>
#include "kstring.h"

void *kmemmove(void *dst, const void *src, size_t size)
{
    if (dst < src && (uintptr_t)dst + size > (uintptr_t)src)
        while (size--)
            ((char *)dst)[size] = ((const char *)src)[size];

    else
        for (size_t i = 0; i < size; ++i)
            ((char *)dst)[i] = ((const char *)src)[i];

    return dst;
}
