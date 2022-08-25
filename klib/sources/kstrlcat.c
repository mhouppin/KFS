#include "kstring.h"

size_t kstrlcat(char *restrict dst, const char *restrict src, size_t size)
{
    size_t dstlen = kstrnlen(dst, size);
    size_t srclen = kstrlen(src);

    if (dstlen != size)
    {
        if (srclen >= size - dstlen)
        {
            kmemcpy(dst + dstlen, src, size - dstlen - 1);
                dst[size - 1] = '\0';
        }
        else
            kmemcpy(dst + dstlen, src, srclen + 1);
    }

    return dstlen + srclen;
}
