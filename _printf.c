#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/* ---------------- basic helpers ---------------- */

int _putchar(char c)
{
    return (write(1, &c, 1));
}

int _puts(const char *s)
{
    int n = 0;

    if (!s)
        s = "(null)";
    while (*s)
        n += _putchar(*s++);
    return (n);
}

/* print numbers in base (10, 16, 8, 2) */
int print_unsigned(unsigned long n, int base, int upper)
{
    char digits[] = "0123456789abcdef";
    char DIGITS[] = "0123456789ABCDEF";
    char buf[65];
    int i = 0, count = 0;
    char *use = upper ? DIGITS : digits;

    if (n == 0)
        return (_putchar('0'));

    while (n > 0)
    {
        buf[i++] = use[n % base];
        n /= base;
    }
    while (i--)
        count += _putchar(buf[i]);
    return (count);
}

int print_signed(long n, int plus, int space)
{
    unsigned long u;
    int count = 0;

    if (n < 0)
    {
        count += _putchar('-');
        u = -n;
    }
    else
    {
        if (plus)
            count += _putchar('+');
        else if (space)
            count += _putchar(' ');
        u = n;
    }
    return (count + print_unsigned(u, 10, 0));
}

/* ---------------- conversion handler ---------------- */

int handle_spec(char sp, va_list ap, int plus, int space, int hash, int lenmod)
{
    int count = 0;

    if (sp == 'c')
        return (_putchar(va_arg(ap, int)));
    else if (sp == 's')
        return (_puts(va_arg(ap, char *)));
    else if (sp == '%')
        return (_putchar('%'));
    else if (sp == 'd' || sp == 'i')
    {
        long v = (lenmod == 2) ? va_arg(ap, long) :
                 (lenmod == 1) ? (short)va_arg(ap, int) :
                                  va_arg(ap, int);
        return (print_signed(v, plus, space));
    }
    else if (sp == 'u' || sp == 'o' || sp == 'x' || sp == 'X')
    {
        unsigned long u = (lenmod == 2) ? va_arg(ap, unsigned long) :
                           (lenmod == 1) ? (unsigned short)va_arg(ap, unsigned int) :
                                           va_arg(ap, unsigned int);
        int base = (sp == 'o') ? 8 : (sp == 'u') ? 10 : 16;
        if (hash && u != 0)
        {
            if (sp == 'o') count += _putchar('0');
            else if (sp == 'x') { count += _putchar('0'); count += _putchar('x'); }
            else if (sp == 'X') { count += _putchar('0'); count += _putchar('X'); }
        }
        return (count + print_unsigned(u, base, (sp == 'X')));
    }
    else if (sp == 'p')
    {
        void *ptr = va_arg(ap, void *);
        if (!ptr)
            return (_puts("(nil)"));
        count += _puts("0x");
        return (count + print_unsigned((unsigned long)ptr, 16, 0));
    }
    return (0);
}

/* ---------------- main printf ---------------- */

int _printf(const char *format, ...)
{
    va_list ap;
    int count = 0;
    int plus, space, hash, lenmod;

    if (!format)
        return (-1);

    va_start(ap, format);
    while (*format)
    {
        if (*format != '%')
        {
            count += _putchar(*format++);
            continue;
        }
        format++; /* skip % */

        /* reset flags */
        plus = space = hash = 0;
        lenmod = 0;

        /* flags */
        while (*format == '+' || *format == ' ' || *format == '#')
        {
            if (*format == '+') plus = 1;
            else if (*format == ' ') space = 1;
            else if (*format == '#') hash = 1;
            format++;
        }

        /* length modifiers */
        if (*format == 'h') { lenmod = 1; format++; }
        else if (*format == 'l') { lenmod = 2; format++; }

        /* specifier */
        if (*format)
            count += handle_spec(*format++, ap, plus, space, hash, lenmod);
    }
    va_end(ap);
    return (count);
}

