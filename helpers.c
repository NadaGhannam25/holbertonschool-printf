#include "main.h"
#include <unistd.h>

/**
 * _puts_number - write a number in any base to buffer
 * @n: number to print
 * @base: numeric base (2,8,10,16)
 * @uppercase: 1 for uppercase hex, 0 for lowercase
 * @buf: buffer array
 * @index: pointer to current buffer index
 *
 * Return: number of characters added
 */
int _puts_number(long n, int base, int uppercase, char *buf, int *index)
{
	char b[32];
	char *digits;
	int i = 0, j, count = 0;
	unsigned long num;

	digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

	if (base == 10 && n < 0)
	{
		count += _putc_buffered('-', buf, index);
		num = -n;
	}
	else
		num = n;

	if (num == 0)
		return (count + _putc_buffered('0', buf, index));

	while (num > 0)
	{
		b[i++] = digits[num % base];
		num /= base;
	}

	for (j = i - 1; j >= 0; j--)
		count += _putc_buffered(b[j], buf, index);

	return (count);
}

