#include <stdint.h>
#include "kstring.h"

char *kstrchr(const char *str, int c)
{
    return c == 0 ? (char *)(uintptr_t)str + kstrlen(str) : kstrchrnul(str, c);
}
