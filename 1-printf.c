#include <stdarg.h>
#include "main.h"

static int _print_number(int n)
{
    int count = 0;
    char digit;

    if (n < 0)
    {
        _putchar('-');
        count++;
        if (n == -2147483648)
        {
            _putstr("2147483648");
            return count + 10;
        }
        n = -n;
    }

    if (n / 10)
        count += _print_number(n / 10);

    digit = (n % 10) + '0';
    _putchar(digit);
    count++;

    return count;
}

int _printf(const char *format, ...)
{
    va_list ap;
    int i = 0, count = 0, res;

    va_start(ap, format);
    while (format[i])
    {
        if (format[i] == 'c')
            count += _putchar(va_arg(ap, int));
        else if (format[i] == 's')
            count += _putstr(va_arg(ap, char *));
        else if (format[i] == '%')
            count += _putchar('%');
        else if (format[i] == 'd' || format[i] == 'i')
        {
            int num = va_arg(ap, int);
            res = _print_number(num);
            if (res < 0)
            {
                va_end(ap);
                return -1;
            }
            count += res;
        }
        else
            count += _putchar(format[i]);
        i++;
    }
    va_end(ap);
    return count;
}
