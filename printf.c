#include "main.h"

/**
 * _printf - produces output according to a format
 * @format: format string containing format specifiers
 * Return: number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    if (!format || (format[0] == '%' && format[1] == '\0'))
        return (-1);

    va_start(args, format);
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == '\0')
            {
                va_end(args);
                return (-1);
            }
            if (*format == 'c')
                count += _putchar(va_arg(args, int));
            else if (*format == 's')
                count += _putstr(va_arg(args, char *));
            else if (*format == '%')
                count += _putchar('%');
            else if (*format == 'd' || *format == 'i')
                count += _print_number(va_arg(args, long));
            else
            {
                count += _putchar('%');
                count += _putchar(*format);
            }
        }
        else
        {
            count += _putchar(*format);
        }
        format++;
    }
    va_end(args);
    return (count);
}
