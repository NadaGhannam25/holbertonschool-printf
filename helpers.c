#include "main.h"
#include <unistd.h>

#define BUF_SIZE 1024

static char buffer[BUF_SIZE];
static int buf_index = 0;

/**
 * _putc_buffered - writes one char to buffer, flush if full
 * @c: char to write
 * @buf: buffer array
 * @index: current buffer index
 * Return: 1 on success
 */
int _putc_buffered(char c, char *buf, int *index)
{
	if (*index >= BUF_SIZE)
		*index = 0;
	buf[(*index)++] = c;
	if (*index == BUF_SIZE)
	{
		write(1, buf, BUF_SIZE);
		*index = 0;
	}
	return (1);
}

/**
 * flush_buffer - flush remaining chars in buffer
 * @buf: buffer array
 * @index: current buffer index
 */
void flush_buffer(char *buf, int *index)
{
	if (*index > 0)
		write(1, buf, *index);
	*index = 0;
}

/**
 * _puts - writes string to buffer
 * @s: string to print
 * Return: number of chars printed
 */
int _puts(char *s)
{
	int count = 0, i = 0;

	if (!s)
		s = "(null)";
	while (s[i])
		count += _putc_buffered(s[i++], buffer, &buf_index);
	return (count);
}

/**
 * _puts_number - prints number in any base
 * @n: number to print
 * @base: base (2,8,10,16)
 * @uppercase: 1 for uppercase hex, 0 for lowercase
 * @buf: buffer array
 * @index: current buffer index
 * Return: number of chars printed
 */
int _puts_number(long n, int base, int uppercase, char *buf, int *index)
{
	char digits[] = "0123456789abcdef";
	char digits_u[] = "0123456789ABCDEF";
	char tmp[65];
	int i = 0, count = 0;
	unsigned long num;

	if (uppercase)
	{
		for (i = 0; i < 16; i++)
			digits[i] = digits_u[i];
	}
	i = 0;

	if (n == 0)
		return (_putc_buffered('0', buf, index));

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
		count += _putc_buffered(tmp[i], buf, index);

	return (count);
}

