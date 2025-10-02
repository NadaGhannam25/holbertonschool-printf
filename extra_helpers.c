#include "main.h"
#include <limits.h>

/**
 * apply_flags - applies +, space, # flags to a number
 * @n: number
 * @base: number base
 * @flag: character flag ('+', ' ', '#')
 *
 * Return: number of characters printed
 */
int apply_flags(long n, int base, char flag)
{
    int count = 0;

    if ((flag == '+' || flag == ' ') && n >= 0)
        count += _putc(flag == '+' ? '+' : ' ');

    if (flag == '#' && base == 16 && n != 0)
        count += _puts("0x");
    else if (flag == '#' && base == 8 && n != 0)
        count += _putc('0');

    return count;
}

/**
 * convert_length - adjust number according to length modifier
 * @n: number (as long)
 * @length: 'l' or 'h'
 *
 * Return: adjusted number
 */
long convert_length(long n, char length)
{
    if (length == 'h')
        n = (short)n;
    else if (length == 'l')
        n = (long)n;
    return n;
}

