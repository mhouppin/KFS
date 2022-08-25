#include "kstring.h"

void *kmemcpy(void *dst, const void *src, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        ((char *)dst)[i] = ((const char *)src)[i];

    return dst;
}
