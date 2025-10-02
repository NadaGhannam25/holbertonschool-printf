#include "main.h"
#include <unistd.h>

#define BUF_SIZE 1024

static char buffer[BUF_SIZE];
static int buf_index = 0;

/**
 * _putc_buffered - write one char to buffer, flush if full
 * @c: char to write
 * Return: 1 on success
 */
int _putc_buffered(char c)
{
	if (buf_index >= BUF_SIZE)
		buf_index = 0;
	buffer[buf_index++] = c;
	if (buf_index == BUF_SIZE)
	{
		write(1, buffer, BUF_SIZE);
		buf_index = 0;
	}
	return (1);
}

/**
 * flush_buffer - flush remaining chars in buffer
 */
void flush_buffer(void)
{
	if (buf_index > 0)
		write(1, buffer, buf_index);
	buf_index = 0;
}

/**
 * _puts_number - prints number in any base
 * @n: number to print
 * @base: base (2,8,10,16)
 * @uppercase: 1 for uppercase hex, 0 for lowercase
 * Return: number of chars printed
 */
int _puts_number(long n, int base, int uppercase)
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
		return (_putc_buffered('0'));

	if (n < 0)
		num = -n;
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

