#include "main.h"

/**
 * print_number - print signed number into buffer
 * @buf: buffer
 * @idx: pointer to index
 * @n: number
 *
 * Return: chars added
 */
int print_number(char *buf, int *idx, long n)
{
	char tmp[32];
	int i = 0, cnt = 0;
	unsigned long num;

	if (n < 0)
	{
		buf_putc(buf, idx, '-');
		num = (unsigned long)(-(n + 1)) + 1;
	}
	else
		num = (unsigned long)n;
	if (num == 0)
		tmp[i++] = '0';
	while (num > 0)
	{
		tmp[i++] = '0' + (num % 10);
		num /= 10;
	}
	while (i--)
	{
		buf_putc(buf, idx, tmp[i]);
		cnt++;
	}
	return (cnt + (n < 0 ? 1 : 0));
}

/**
 * print_unsigned_num_base - print unsigned number in given base
 * @buf: buffer
 * @idx: pointer to index
 * @n: number
 * @base: base
 * @uppercase: 1 for uppercase
 *
 * Return: chars added
 */
int print_unsigned_num_base(char *buf, int *idx, unsigned long n,
			    int base, int uppercase)
{
	char tmp[65];
	const char *digits_low = "0123456789abcdef";
	const char *digits_up = "0123456789ABCDEF";
	const char *digits = uppercase ? digits_up : digits_low;
	int i = 0, cnt = 0;

	if (n == 0)
		tmp[i++] = '0';
	while (n > 0)
	{
		tmp[i++] = digits[n % base];
		n /= base;
	}
	while (i--)
	{
		buf_putc(buf, idx, tmp[i]);
		cnt++;
	}
	return (cnt);
}

