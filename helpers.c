#include "main.h"
#include <unistd.h>

/**
 * _putc - writes a single character to stdout
 * @c: character to print
 *
 * Return: 1 on success
 */
int _putc(char c)
{
    return (write(1, &c, 1) == 1 ? 1 : 0);
}

/**
 * _puts - writes a string to stdout
 * @s: string to print
 *
 * Return: number of characters printed
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
    return (n);
}

/**
 * _puts_number - prints a number in a given base
 * @n: number to print
 * @base: base (2, 8, 10, 16)
 * @uppercase: use uppercase letters for hex
 *
 * Return: number of characters printed
 */
int _puts_number(long n, int base, int uppercase)
{
    char buf[65];
    char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    int i = 64, count = 0;
    unsigned long num;

    buf[i--] = '\0';
    if (n < 0)
        num = -n;
    else
        num = n;

    do {
        buf[i--] = digits[num % base];
        num /= base;
    } while (num != 0);

    if (n < 0 && base == 10)
        buf[i--] = '-';

    i++;
    while (buf[i])
        count += _putc(buf[i++]);

    return count;
}

