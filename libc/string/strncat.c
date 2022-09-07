#include <string.h>

char *strncat(char *restrict dst, const char *restrict src, size_t size)
{
    char *p = dst;
    size_t i;

    while (*p)
        ++p;

    for (i = 0; i < size && src[i]; ++i)
        p[i] = src[i];

    p[i] = 0;
    return dst;
}
