#include <string.h>

void *memset(void *b, int c, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        ((char *)b)[i] = c;

    return b;
}
