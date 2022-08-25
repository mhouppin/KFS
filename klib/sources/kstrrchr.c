#include <stdint.h>
#include "kstring.h"

char *kstrrchr(const char *str, int c)
{
    if (c == 0)
        return (char *)str + kstrlen(str);

    char *last = NULL;

    while (*str)
    {
        if (*str == c)
            last = (char *)str;
        ++str;
    }

    return last;
}
