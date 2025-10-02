#include "main.h"
#include <unistd.h>

/**
 * _putc - writes a single character to stdout
 * @c: character to write
 *
 * Return: 1 on success, 0 otherwise
 */
int _putc(char c)
{
	return (write(1, &c, 1) == 1 ? 1 : 0);
}

/**
 * _puts - writes a string to stdout
 * @s: string to write (prints "(null)" if s is NULL)
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
 * _puts_number - writes a number in any base
 * @n: number to print
 * @base: numeric base (2, 8, 10, 16)
 * @uppercase: 1 for uppercase hex, 0 for lowercase
 *
 * Return: number of characters printed
 */
int _puts_number(long n, int base, int uppercase)
{
	char buf[32];
	char *digits;
	int i = 0, j, count = 0;
	unsigned long num;

	digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

	if (base == 10 && n < 0)
	{
		count += _putc('-');
		num = -n;
	}
	else
		num = n;

	if (num == 0)
		return (count + _putc('0'));

	while (num > 0)
	{
		buf[i++] = digits[num % base];
		num /= base;
	}

	for (j = i - 1; j >= 0; j--)
		count += _putc(buf[j]);

	return (count);
}

