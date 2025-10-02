#include "main.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

/**
 * _putc - write one character to stdout
 * @c: character
 *
 * Return: 1 on success
 */
int _putc(char c)
{
    return write(1, &c, 1) == 1 ? 1 : 0;
}

/**
 * _puts - write a string to stdout
 * @s: string
 *
 * Return: number of chars printed
 */
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

/**
 * _puts_number - print number with base and flags
 * @n: number to print
 * @base: base (2, 8, 10, 16)
 * @uppercase: 1 for uppercase hex
 * @flags: bitwise flags (plus, space, hash)
 *
 * Return: chars printed
 */
int _puts_number(long n, int base, int uppercase, int flags)
{
    char buf[65];
    char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    unsigned long num;
    int i = 0, j, count = 0;

    if (base == 10 && n < 0)
    {
        count += _putc('-');
        num = -n;
    }
    else
        num = (unsigned long)n;

    if (num == 0)
    {
        if (flags & FLAG_PLUS)
            count += _putc('+');
        else if (flags & FLAG_SPACE)
            count += _putc(' ');
        return count + _putc('0');
    }

    while (num > 0)
    {
        buf[i++] = digits[num % base];
        num /= base;
    }

    if ((flags & FLAG_HASH) && base == 8)
        count += _putc('0');
    else if ((flags & FLAG_HASH) && base == 16)
        count += _putc('0') + _putc(uppercase ? 'X' : 'x');
    else if ((flags & FLAG_PLUS) && base == 10 && n >= 0)
        count += _putc('+');
    else if ((flags & FLAG_SPACE) && base == 10 && n >= 0)
        count += _putc(' ');

    for (j = i - 1; j >= 0; j--)
        count += _putc(buf[j]);

    return count;
}

