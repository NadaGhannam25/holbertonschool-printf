#include "main.h"
#include <unistd.h>

#define BUF_SIZE 1024

static char buffer[BUF_SIZE];
static int buf_index = 0;

/**
 * _putc_buffered - write a char to buffer, flush if full
 * @c: char to write
 * Return: 1
 */
int _putc_buffered(char c)
{
	buffer[buf_index++] = c;
	if (buf_index >= BUF_SIZE)
	{
		write(1, buffer, BUF_SIZE);
		buf_index = 0;
	}
	return (1);
}

/**
 * flush_buffer - flush remaining chars
 */
void flush_buffer(void)
{
	if (buf_index > 0)
		write(1, buffer, buf_index);
	buf_index = 0;
}

/**
 * _puts_number - print number in any base with flags
 * @n: number
 * @base: base
 * @uppercase: 1 for hex uppercase
 * @flag_plus: 1 to print '+' for positive
 * @flag_space: 1 to print ' ' for positive
 * Return: chars printed
 */
int _puts_number(long n, int base, int uppercase, int flag_plus, int flag_space)
{
	char digits[] = "0123456789abcdef";
	char digits_u[] = "0123456789ABCDEF";
	char tmp[65];
	int i = 0, count = 0;
	unsigned long num;

	if (uppercase)
		for (i = 0; i < 16; i++)
			digits[i] = digits_u[i];
	i = 0;

	if (n == 0)
	{
		if (flag_plus)
			count += _putc_buffered('+');
		else if (flag_space)
			count += _putc_buffered(' ');
		return count + _putc_buffered('0');
	}

	if (n < 0)
	{
		count += _putc_buffered('-');
		num = -n;
	}
	else
		num = n;

	while (num > 0)
	{
		tmp[i++] = digits[num % base];
		num /= base;
	}

	for (--i; i >= 0; i--)
		count += _putc_buffered(tmp[i]);

	return (count);
}

