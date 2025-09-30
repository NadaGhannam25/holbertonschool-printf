#include "main.h"

/**
 * _printf - produces output according to a format
 * @format: format string
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
    convert p[] = {
        {"%s", print_s}, {"%c", print_c},
        {"%%", print_37},
        {"%d", print_d}, {"%i", print_i}
    };

    va_list args;
    int i = 0, j, length = 0;

    va_start(args, format);
    if (format == NULL || (format[0] == '%' && format[1] == '\0'))
        return (-1);

Here:
    while (format[i] != '\0')
    {
        j = 4;
        while (j >= 0)
        {
            if (p[j].ph[0] == format[i] && p[j].ph[1] == format[i + 1])
            {
                length += p[j].function(args);
                i += 2;
                goto Here;
            }
            j--;
        }
        _putchar(format[i]);
        length++;
        i++;
    }
    va_end(args);
    return (length);
}

