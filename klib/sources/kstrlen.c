#include "kstring.h"

size_t kstrlen(const char *str)
{
    size_t i = 0;

    while (str[i])
        ++i;

    return i;
}
