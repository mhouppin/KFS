#include "kstring.h"

char *kstrncpy(char *restrict dst, const char *restrict src, size_t size)
{
    size_t i;

    for (i = 0; i < size; ++i)
    {
        dst[i] = src[i];

        if (!src[i])
            break ;
    }

    while (i < size)
    {
        dst[i] = 0;
        ++i;
    }

    return dst;
}
