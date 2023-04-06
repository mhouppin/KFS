#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static const char *static_itoa(int value)
{
    static unsigned char buffer[13] = {0};
    unsigned int uvalue = (unsigned int)((value < 0) ? -value : value);
    int i = 11;

    while (1)
    {
        buffer[i] = uvalue % 10 + '0';
        uvalue /= 10;

        if (uvalue == 0)
            break ;

        --i;
    }

    if (value < 0)
        buffer[--i] = '-';

    return (const char *)&buffer[i];
}

static const char *static_uint_to_base(unsigned int uvalue, const char *base_charset)
{
    static unsigned char buffer[32] = {0};

    if (base_charset == NULL || base_charset[0] == '\0' || base_charset[1] == '\0')
        return NULL;

    const int base = strlen(base_charset);
    
    int i = 31;

    while (1)
    {
        buffer[i] = base_charset[uvalue % base];
        uvalue /= base;

        if (uvalue == 0)
            break ;

        --i;
    }

    return (const char *)&buffer[i];
}

static bool try_print(const char *data, size_t size)
{
    const unsigned char *bytes = (const unsigned char *)data;

    for (size_t i = 0; i < size; ++i)
        if (putchar(bytes[i]) == EOF)
            return false;

    return true;
}

int printf(const char *restrict format, ...)
{
    int ret = 0;
    va_list ap;

    va_start(ap, format);

    while (*format != '\0')
    {
        size_t max_write = (size_t)(INT_MAX - ret);

        if (format[0] != '%' || format[1] == '%')
        {
            if (format[0] == '%')
                ++format;

            size_t size = 1;

            while (format[size] != '\0' && format[size] != '%')
                ++size;

            if (max_write < size)
            {
                // TODO: set errno to EOVERFLOW.
                return -1;
            }

            if (!try_print(format, size))
                return -1;

            format += size;
            ret += size;
            continue ;
        }

        ++format;

        if (*format == 'c')
        {
            ++format;

            char c = (char)va_arg(ap, int);

            if (max_write == 0)
            {
                // TODO: set errno to EOVERFLOW.
                return -1;
            }

            if (!try_print(&c, sizeof(char)))
                return -1;

            ++ret;
        }
        else if (*format == 's')
        {
            ++format;

            const char *str = va_arg(ap, const char *);
            size_t len = strnlen(str, max_write + 1);

            if (max_write < len)
            {
                // TODO: set errno to EOVERFLOW.
                return -1;
            }

            if (!try_print(str, len))
                return -1;

            ret += len;
        }
        else if (*format == 'd')
        {
            ++format;

            const char *str = static_itoa(va_arg(ap, int));
            size_t len = strnlen(str, max_write + 1);

            if (max_write < len)
            {
                // TODO: set errno to EOVERFLOW.
                return -1;
            }

            if (!try_print(str, len))
                return -1;

            ret += len;
        }
        else if (*format == 'x')
        {
            ++format;

            const char *str = static_uint_to_base(va_arg(ap, int), "0123456789abcdef");	
            size_t len = strnlen(str, max_write + 1);

            if (max_write < len)
            {
                // TODO: set errno to EOVERFLOW.
                return -1;
            }

            if (!try_print(str, len))
                return -1;

            ret += len;
        }
        else
        {
            if (max_write == 0)
            {
                // TODO: set errno to EOVERFLOW.
                return -1;
            }

            if (!try_print(format, 1))
                return -1;

            ++format;
            ++ret;
        }
    }

    va_end(ap);
    return ret;
}
