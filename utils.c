#include "main.h"

/**
 * flush_buffer - write out buffer to stdout
 * @buf: buffer
 * @idx: pointer to index
 *
 * Return: number of bytes written
 */
int flush_buffer(char *buf, int *idx)
{
	int w;

	if (*idx <= 0)
		return (0);
	w = write(1, buf, *idx);
	*idx = 0;
	return (w);
}

/**
 * buf_putc - append char to buffer, flush if full
 * @buf: buffer
 * @idx: pointer to index
 * @c: char to append
 *
 * Return: 1 on success, -1 on error
 */
int buf_putc(char *buf, int *idx, char c)
{
	int ret;

	buf[*idx] = c;
	(*idx)++;
	if (*idx >= BUFSIZE)
	{
		ret = flush_buffer(buf, idx);
		if (ret < 0)
			return (-1);
	}
	return (1);
}

/**
 * buf_append - append string of len chars to buffer
 * @buf: buffer
 * @idx: pointer to index
 * @s: string
 * @len: length
 *
 * Return: number of chars appended
 */
int buf_append(char *buf, int *idx, const char *s, int len)
{
	int i;

	for (i = 0; i < len; i++)
	{
		if (buf_putc(buf, idx, s[i]) < 0)
			return (-1);
	}
	return (len);
}

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

/**
 * print_pointer - print pointer as hex
 * @buf: buffer
 * @idx: pointer to index
 * @p: pointer
 *
 * Return: chars added
 */
int print_pointer(char *buf, int *idx, void *p)
{
	unsigned long addr = (unsigned long)p;
	int cnt = 0;

	buf_putc(buf, idx, '0');
	buf_putc(buf, idx, 'x');
	cnt += 2;
	cnt += print_unsigned_num_base(buf, idx, addr, 16, 0);
	return (cnt);
}

