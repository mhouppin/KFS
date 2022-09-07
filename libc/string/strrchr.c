#include <stdint.h>
#include <string.h>

char *strrchr(const char *str, int c)
{
    if (c == 0)
        return (char *)str + strlen(str);

    char *last = NULL;

    while (*str)
    {
        if (*str == c)
            last = (char *)str;
        ++str;
    }

    return last;
}
