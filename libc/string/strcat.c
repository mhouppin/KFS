#include <string.h>

char *strcat(char *restrict dst, const char *restrict src)
{
    char *p = dst;
    size_t i;

    while (*p)
        ++p;

    for (i = 0; src[i]; ++i)
        p[i] = src[i];

    p[i] = 0;
    return dst;
}
