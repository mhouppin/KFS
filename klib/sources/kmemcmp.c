#include "kstring.h"

int kmemcmp(const void *s1, const void *s2, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        unsigned char u1 = ((const unsigned char *)s1)[i];
        unsigned char u2 = ((const unsigned char *)s2)[i];

        if (u1 != u2)
            return (int)u1 - (int)u2;
    }

    return 0;
}
