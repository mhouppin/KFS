#include "kstring.h"

void *kmemccpy(void *restrict dst, const void *restrict src, int c, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        char v = ((const char *)src)[i];
        ((char *)dst)[i] = v;

        if (v == c)
            return (void *)((char *)dst + i + 1);
    }

    return NULL;
}
