#ifndef KSTRING_H
#define KSTRING_H

#include <stddef.h>

void *kmemccpy(void *restrict dst, const void *restrict src, int c, size_t size);
void *kmemchr(const void *b, int c, size_t size);
int kmemcmp(const void *s1, const void *s2, size_t size);
void *kmemcpy(void *restrict dst, const void *restrict src, size_t size);
void *kmemmove(void *dst, const void *src, size_t size);
void *kmemset(void *b, int c, size_t size);
char *kstrcat(char *restrict dst, const char *restrict src);
char *kstrchr(const char *str, int c);
char *kstrchrnul(const char *str, int c);
char *kstrcpy(char *restrict dst, const char *restrict src);
size_t kstrlcat(char *restrict dst, const char *restrict src, size_t size);
size_t kstrlen(const char *str);
char *kstrncat(char *restrict dst, const char *restrict src, size_t size);
char *kstrncpy(char *restrict dst, const char *restrict src, size_t size);
size_t kstrnlen(const char *str, size_t size);
char *kstrrchr(const char *str, int c);

#endif
