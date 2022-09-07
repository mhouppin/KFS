#include <stdint.h>
#include <string.h>

char *strchr(const char *str, int c)
{
    return c == 0 ? (char *)(uintptr_t)str + strlen(str) : strchrnul(str, c);
}
