#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

/**
 * _putc - write one character to stdout
 * @c: character
 *
 * Return: 1 on success
 */
static int _putc(char c)
{
    return (write(1, &c, 1) == 1 ? 1 : 0);
}

/**
 * _puts - write a C string to stdout
 * @s: string (prints "(null)" if s is NULL)
 *
 * Return: number of bytes written
 */
static int _puts(const char *s)
{
    int n = 0;

    if (!s)
        s = "(null)";
    while (s[n])
        n++;
    if (n)
        write(1, s, n);
    return (n);
}

/**
 * _puts_int - write an integer to stdout
 * @n: integer to print
 *
 * Return: number of characters printed
 */
static int _puts_int(int n)
{
    char buf[12];
    int i = 0, j, count = 0;
    unsigned int num;

    if (n < 0)
    {
        count += _putc('-');
        num = -n;
    }
    else
        num = n;

    if (num == 0)
        return count + _putc('0');

    while (num > 0)
    {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    for (j = i - 1; j >= 0; j--)
        count += _putc(buf[j]);

    return count;
}

/**
 * print_conv - handle one conversion specifier
 * @sp: specifier character ('c', 's', '%', 'd', 'i')
 * @ap: address of the variadic list
 *
 * Return: number of chars printed for this specifier
 */
static int print_conv(char sp, va_list *ap)
{
    if (sp == 'c')
        return (_putc((char)va_arg(*ap, int)));
    if (sp == 's')
        return (_puts(va_arg(*ap, char *)));
    if (sp == '%')
        return (_putc('%'));
    if (sp == 'd' || sp == 'i')
        return (_puts_int(va_arg(*ap, int)));

    return (_putc('%') + _putc(sp));
}

/**
 * _printf - produces output according to a format
 * @format: format string (supports %c, %s, %%, %d, %i)
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
            count += print_conv(format[i++], &ap);
        }
    }
    va_end(ap);
    return (count);
}
