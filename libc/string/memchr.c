#include <stdint.h>
#include <string.h>

void *memchr(const void *b, int c, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        if (((const char *)b)[i] == c)
            return (char *)((uintptr_t)b + i);

    return NULL;
}
