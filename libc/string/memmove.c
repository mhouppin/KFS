#include <stdint.h>
#include <string.h>

void *memmove(void *dst, const void *src, size_t size)
{
    if (dst > src && (uintptr_t)dst < (uintptr_t)src + size)
        while (size--)
            ((char *)dst)[size] = ((const char *)src)[size];

    else
        for (size_t i = 0; i < size; ++i)
            ((char *)dst)[i] = ((const char *)src)[i];

    return dst;
}
