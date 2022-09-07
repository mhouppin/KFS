#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memccpy(void *__restrict dst, const void *__restrict src, int c, size_t size);
void *memchr(const void *b, int c, size_t size);
int memcmp(const void *s1, const void *s2, size_t size);
void *memcpy(void *__restrict dst, const void *__restrict src, size_t size);
void *memmove(void *dst, const void *src, size_t size);
void *memset(void *b, int c, size_t size);
char *strcat(char *__restrict dst, const char *__restrict src);
char *strchr(const char *str, int c);
char *strchrnul(const char *str, int c);
char *strcpy(char *__restrict dst, const char *__restrict src);
size_t strlcat(char *__restrict dst, const char *__restrict src, size_t size);
size_t strlen(const char *str);
char *strncat(char *__restrict dst, const char *__restrict src, size_t size);
char *strncpy(char *__restrict dst, const char *__restrict src, size_t size);
size_t strnlen(const char *str, size_t size);
char *strrchr(const char *str, int c);

#ifdef __cplusplus
}
#endif

#endif
