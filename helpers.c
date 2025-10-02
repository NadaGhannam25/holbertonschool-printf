#include "main.h"
#include <unistd.h>

/**
 * _putc - write one character to stdout
 * @c: character
 * Return: 1
 */
int _putc(char c)
{
	return (write(1, &c, 1) == 1 ? 1 : 0);
}

/**
 * _puts - write a string to stdout
 * @s: string
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
 * _puts_number - write number in given base
 * @n: number
 * @base: number base
 * @uppercase: 1 for upper hex
 * Return: number of chars printed
 */
int _puts_number(long n, int base, int uppercase)
{
	char buf[65], *digits;
	int i = 64, neg = 0, count = 0;

	digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
	buf[i--] = '\0';

	if (n == 0)
		return (_putc('0'));

	if (base == 10 && n < 0)
	{
		neg = 1;
		n = -n;
	}

	while (n > 0)
	{
		buf[i--] = digits[n % base];
		n /= base;
	}
	if (neg)
		buf[i--] = '-';

	count = _puts(&buf[i + 1]);
	return (count);
}

