#include <string.h>

size_t strnlen(const char *str, size_t size)
{
    size_t i = 0;

    while (i < size && str[i])
        ++i;

    return i;
}
