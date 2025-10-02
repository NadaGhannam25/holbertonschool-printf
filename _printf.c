#include "main.h"
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>


#define FLAG_PLUS  1
#define FLAG_SPACE 2
#define FLAG_HASH  4


int _putc(char c)
{
    return write(1, &c, 1);
}


int _puts(const char *s)
{
    int n = 0;
    if (!s)
        s = "(null)";
    while (s[n])
        n++;
    if (n)
        write(1, s, n);
    return n;
}


int _puts_number_mod(long long num, int base, int uppercase, int flags)
{
    char buf[65];
    char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    unsigned long long n;
    int i = 0, j, count = 0;

    if ((base == 10) && num < 0)
    {
        count += _putc('-');
        n = -num;
    }
    else
        n = (unsigned long long)num;

    if (n == 0)
        buf[i++] = '0';

    while (n > 0)
    {
        buf[i++] = digits[n % base];
        n /= base;
    }

    if (flags & FLAG_HASH)
    {
        if (base == 8 && buf[i - 1] != '0')
            buf[i++] = '0';
        else if (base == 16)
        {
            buf[i++] = uppercase ? 'X' : 'x';
            buf[i++] = '0';
        }
    }

    if ((flags & FLAG_PLUS) && base == 10 && num >= 0)
        count += _putc('+');
    else if ((flags & FLAG_SPACE) && base == 10 && num >= 0)
        count += _putc(' ');

    for (j = i - 1; j >= 0; j--)
        count += _putc(buf[j]);

    return count;
}

int print_conv_mod(char fmt, va_list *ap, char length, int flags)
{
    long long n;
    unsigned long long u;

    if (length == 'l') 
    {
        if (fmt == 'd' || fmt == 'i')
            return _puts_number_mod(va_arg(*ap, long), 10, 0, flags);
        else if (fmt == 'u')
            return _puts_number_mod(va_arg(*ap, unsigned long), 10, 0, flags);
        else if (fmt == 'o')
            return _puts_number_mod(va_arg(*ap, unsigned long), 8, 0, flags);
        else if (fmt == 'x')
            return _puts_number_mod(va_arg(*ap, unsigned long), 16, 0, flags);
        else if (fmt == 'X')
            return _puts_number_mod(va_arg(*ap, unsigned long), 16, 1, flags);
    }
    else if (length == 'h') 
    {
        if (fmt == 'd' || fmt == 'i')
            return _puts_number_mod((short)va_arg(*ap, int), 10, 0, flags);
        else if (fmt == 'u')
            return _puts_number_mod((unsigned short)va_arg(*ap, unsigned int), 10, 0, flags);
        else if (fmt == 'o')
            return _puts_number_mod((unsigned short)va_arg(*ap, unsigned int), 8, 0, flags);
        else if (fmt == 'x')
            return _puts_number_mod((unsigned short)va_arg(*ap, unsigned int), 16, 0, flags);
        else if (fmt == 'X')
            return _puts_number_mod((unsigned short)va_arg(*ap, unsigned int), 16, 1, flags);
    }

    
    if (fmt == 'd' || fmt == 'i')
        return _puts_number_mod(va_arg(*ap, int), 10, 0, flags);
    if (fmt == 'u')
        return _puts_number_mod(va_arg(*ap, unsigned int), 10, 0, flags);
    if (fmt == 'o')
        return _puts_number_mod(va_arg(*ap, unsigned int), 8, 0, flags);
    if (fmt == 'x')
        return _puts_number_mod(va_arg(*ap, unsigned int), 16, 0, flags);
    if (fmt == 'X')
        return _puts_number_mod(va_arg(*ap, unsigned int), 16, 1, flags);

    return _putc('%') + _putc(fmt);
}


int parse_flags(const char **format)
{
    int flags = 0;
    while (**format == '+' || **format == ' ' || **format == '#')
    {
        if (**format == '+')
            flags |= FLAG_PLUS;
        else if (**format == ' ')
            flags |= FLAG_SPACE;
        else if (**format == '#')
            flags |= FLAG_HASH;
        (*format)++;
    }
    return flags;
}


int _printf(const char *format, ...)
{
    va_list ap;
    int count = 0;
    char length = 0;

    if (!format)
        return -1;

    va_start(ap, format);
    while (*format)
    {
        if (*format != '%')
        {
            count += _putc(*format++);
            continue;
        }
        format++;
        int flags = parse_flags(&format);

        length = 0;
        if (*format == 'l' || *format == 'h')
        {
            length = *format;
            format++;
        }

        if (!*format)
        {
            va_end(ap);
            return -1;
        }

        count += print_conv_mod(*format++, &ap, length, flags);
    }
    va_end(ap);
    return count;
}

