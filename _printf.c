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
 * _puts_unsigned - write an unsigned integer to stdout
 * @n: unsigned integer to print
 *
 * Return: number of characters printed
 */
static int _puts_unsigned(unsigned int n)
{
    char buf[10];
    int i = 0, j, count = 0;

    if (n == 0)
        return _putc('0');

    while (n > 0)
    {
        buf[i++] = (n % 10) + '0';
        n /= 10;
    }

    for (j = i - 1; j >= 0; j--)
        count += _putc(buf[j]);

    return count;
}

/**
 * _puts_binary - write an unsigned int in binary
 * @n: number to print
 *
 * Return: number of characters printed
 */
static int _puts_binary(unsigned int n)
{
    char buf[32];
    int i = 0, j, count = 0;

    if (n == 0)
        return _putc('0');

    while (n > 0)
    {
        buf[i++] = (n % 2) + '0';
        n /= 2;
    }

    for (j = i - 1; j >= 0; j--)
        count += _putc(buf[j]);

    return count;
}

/**
 * _puts_base - write an unsigned int in any base (octal/hex)
 * @n: number to print
 * @base: base (8 or 16)
 * @uppercase: 1 for uppercase hex, 0 for lowercase
 *
 * Return: number of characters printed
 */
static int _puts_base(unsigned int n, int base, int uppercase)
{
    char buf[32];
    char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    int i = 0, j, count = 0;

    if (n == 0)
        return _putc('0');

    while (n > 0)
    {
        buf[i++] = digits[n % base];
        n /= base;
    }

    for (j = i - 1; j >= 0; j--)
        count += _putc(buf[j]);

    return count;
}

/**
 * print_conv - handle one conversion specifier
 * @sp: specifier character ('c', 's', '%', 'd', 'i', 'b', 'u', 'o', 'x', 'X')
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
    if (sp == 'b')
        return (_puts_binary(va_arg(*ap, unsigned int)));
    if (sp == 'u')
        return (_puts_unsigned(va_arg(*ap, unsigned int)));
    if (sp == 'o')
        return (_puts_base(va_arg(*ap, unsigned int), 8, 0));
    if (sp == 'x')
        return (_puts_base(va_arg(*ap, unsigned int), 16, 0));
    if (sp == 'X')
        return (_puts_base(va_arg(*ap, unsigned int), 16, 1));

    return (_putc('%') + _putc(sp));
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
            count += print_conv(format[i++], &ap);
        }
    }
    va_end(ap);
    return (count);
}
