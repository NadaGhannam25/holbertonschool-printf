#include <stdarg.h>
#include "main.h"

static int _print_number(long n)
{
    int count = 0;
    char digit;

    if (n < 0)
    {
        if (_putchar('-') < 0)
            return -1;
        count++;
        if (n == -2147483648L || n == -9223372036854775807L - 1)
        {
            char *min_val = (n == -2147483648L) ? "2147483648" : "9223372036854775808";
            for (int i = 0; min_val[i]; i++)
            {
                if (_putchar(min_val[i]) < 0)
                    return -1;
                count++;
            }
            return count;
        }
        n = -n;
    }

    if (n / 10)
    {
        int res = _print_number(n / 10);
        if (res < 0)
            return -1;
        count += res;
    }

    digit = (n % 10) + '0';
    if (_putchar(digit) < 0)
        return -1;
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
            long num = va_arg(ap, long);  // هنا نستخدم long بدل int
            res = _print_number(num);
            if (res < 0)
            {
                va_end(ap);
                return -1;
            }
            count += res;
        }
        else
        {
            if (_putchar(format[i]) < 0)
            {
                va_end(ap);
                return -1;
            }
            count++;
        }
        i++;
    }
    va_end(ap);
    return count;
}
