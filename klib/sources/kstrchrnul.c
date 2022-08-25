#include <stdint.h>
#include "kstring.h"

char *kstrchrnul(const char *str, int c)
{
    for (size_t i = 0; str[i]; ++i)
        if (str[i] == c)
            return (char *)((uintptr_t)str + i);

    return NULL;
}
