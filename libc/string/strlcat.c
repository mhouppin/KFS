#include <string.h>

size_t strlcat(char *restrict dst, const char *restrict src, size_t size)
{
    size_t dstlen = strnlen(dst, size);
    size_t srclen = strlen(src);

    if (dstlen != size)
    {
        if (srclen >= size - dstlen)
        {
            memcpy(dst + dstlen, src, size - dstlen - 1);
            dst[size - 1] = '\0';
        }
        else
            memcpy(dst + dstlen, src, srclen + 1);
    }

    return dstlen + srclen;
}
