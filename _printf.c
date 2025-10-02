#include "main.h"
#include <stdarg.h>
#include <limits.h>

/**
 * print_conv - handle conversion specifiers
 * @sp: specifier
 * @ap: variadic list
 *
 * Return: chars printed
 */
static int print_conv(char sp, va_list *ap)
{
    if (sp == 'c')
        return _putc((char)va_arg(*ap, int));
    if (sp == 's')
        return _puts(va_arg(*ap, char *));
    if (sp == '%')
        return _putc('%');
    if (sp == 'd' || sp == 'i')
        return _puts_number(va_arg(*ap, int), 10, 0, 0);
    if (sp == 'u')
        return _puts_number(va_arg(*ap, unsigned int), 10, 0, 0);
    if (sp == 'o')
        return _puts_number(va_arg(*ap, unsigned int), 8, 0, 0);
    if (sp == 'x')
        return _puts_number(va_arg(*ap, unsigned int), 16, 0, 0);
    if (sp == 'X')
        return _puts_number(va_arg(*ap, unsigned int), 16, 1, 0);
    if (sp == 'b')
        return _puts_number(va_arg(*ap, unsigned int), 2, 0, 0);
    if (sp == 'S')
    {
        char *str = va_arg(*ap, char *);
        int count = 0, i = 0;
        unsigned char c;

        if (!str)
            str = "(null)";
        while (str[i])
        {
            c = str[i];
            if (c < 32 || c >= 127)
            {
                count += _putc('\\');
                count += _putc('x');
                count += _putc("0123456789ABCDEF"[c / 16]);
                count += _putc("0123456789ABCDEF"[c % 16]);
            }
            else
                count += _putc(c);
            i++;
        }
        return count;
    }
    if (sp == 'p')
    {
        void *ptr = va_arg(*ap, void *);
        unsigned long addr = (unsigned long)ptr;
        int count = 0;

        if (!ptr)
            return _puts("(nil)");
        count += _puts_number(addr, 16, 0, FLAG_HASH);
        return count;
    }
    return _putc('%') + _putc(sp);
}

/**
 * _printf - formatted output
 * @format: string
 *
 * Return: chars printed
 */
int _printf(const char *format, ...)
{
    va_list ap;
    int count = 0, i = 0;

    if (!format)
        return -1;

    va_start(ap, format);
    while (format[i])
    {
        if (format[i] != '%')
            count += _putc(format[i++]);
        else
        {
            i++;
            if (!format[i])
            {
                va_end(ap);
                return -1;
            }
            count += print_conv(format[i++], &ap);
        }
    }
    va_end(ap);
    return count;
}

