#ifndef KSTRING_H
#define KSTRING_H

#include <stddef.h>

void *kmemcpy(void *dst, const void *src, size_t size);
void *kmemset(void *b, int c, size_t size);
size_t kstrlen(const char *str);

#endif
