#include "main.h"
#include <stdarg.h>

/**
 * print_conv - handles a single conversion specifier with length modifiers
 * @fmt: format string
 * @i: pointer to current index in format string
 * @ap: variadic list
 *
 * Return: number of characters printed
 */
static int print_conv(const char *fmt, int *i, va_list *ap)
{
    int count = 0;
    char sp = fmt[*i];
    char modifier = 0; /* 0 = none, 'h', 'l' */

    /* check for length modifier */
    if (sp == 'h' || sp == 'l')
    {
        modifier = sp;
        (*i)++;
        sp = fmt[*i];
    }

    /* handle specifiers */
    if (sp == 'd' || sp == 'i')
    {
        if (modifier == 'l')
            count = _puts_number(va_arg(*ap, long), 10, 0);
        else if (modifier == 'h')
            count = _puts_number((short)va_arg(*ap, int), 10, 0);
        else
            count = _puts_number(va_arg(*ap, int), 10, 0);
    }
    else if (sp == 'u')
    {
        if (modifier == 'l')
            count = _puts_number(va_arg(*ap, unsigned long), 10, 0);
        else if (modifier == 'h')
            count = _puts_number((unsigned short)va_arg(*ap, unsigned int), 10, 0);
        else
            count = _puts_number(va_arg(*ap, unsigned int), 10, 0);
    }
    else if (sp == 'o')
    {
        if (modifier == 'l')
            count = _puts_number(va_arg(*ap, unsigned long), 8, 0);
        else if (modifier == 'h')
            count = _puts_number((unsigned short)va_arg(*ap, unsigned int), 8, 0);
        else
            count = _puts_number(va_arg(*ap, unsigned int), 8, 0);
    }
    else if (sp == 'x')
    {
        if (modifier == 'l')
            count = _puts_number(va_arg(*ap, unsigned long), 16, 0);
        else if (modifier == 'h')
            count = _puts_number((unsigned short)va_arg(*ap, unsigned int), 16, 0);
        else
            count = _puts_number(va_arg(*ap, unsigned int), 16, 0);
    }
    else if (sp == 'X')
    {
        if (modifier == 'l')
            count = _puts_number(va_arg(*ap, unsigned long), 16, 1);
        else if (modifier == 'h')
            count = _puts_number((unsigned short)va_arg(*ap, unsigned int), 16, 1);
        else
            count = _puts_number(va_arg(*ap, unsigned int), 16, 1);
    }
    else if (sp == 'c')
        count = _putc((char)va_arg(*ap, int));
    else if (sp == 's')
        count = _puts(va_arg(*ap, char *));
    else if (sp == '%')
        count = _putc('%');
    else if (sp == 'b')
        count = _puts_number(va_arg(*ap, unsigned int), 2, 0);
    else if (sp == 'S')
        count = _puts_non_printable(va_arg(*ap, char *));
    else if (sp == 'p')
        count = _puts_pointer(va_arg(*ap, void *));
    else
        count = _putc('%') + _putc(sp);

    return (count);
}

/**
 * _printf - produces output according to a format
 * @format: format string
 *
 * Return: number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
    va_list ap;
    int count = 0, i = 0;

    if (!format)
        return (-1);

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
                return (-1);
            }
            count += print_conv(format, &i, &ap);
            i++;
        }
    }
    va_end(ap);

    return (count);
}

