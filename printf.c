#include "main.h"
#include <stdlib.h>
#include <limits.h>

/**
 * flush_buffer - write out the buffer to stdout and reset index
 * @buf: buffer
 * @idx: pointer to current index
 * Return: number of bytes written or -1 on error
 */
int flush_buffer(char *buf, int *idx)
{
	int w = 0;

	if (*idx <= 0)
		return (0);
	w = write(1, buf, *idx);
	*idx = 0;
	return (w);
}

/**
 * buf_append - append 'len' bytes from s into buf (flush if needed)
 * @buf: buffer
 * @idx: pointer to index
 * @s: source
 * @len: length
 * Return: number of chars appended (len) or -1 on write error
 */
int buf_append(char *buf, int *idx, const char *s, int len)
{
	int i, wrote = 0;

	for (i = 0; i < len; i++)
	{
		if (buf_putc(buf, idx, s[i]) < 0)
			return (-1);
		wrote++;
	}
	return (wrote);
}

/**
 * buf_putc - append single char to buffer, flush if full
 * @buf: buffer
 * @idx: pointer to index
 * @c: char
 * Return: 1 on success or -1 on write error
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
 * print_number - print signed number decimal into buffer (handles INT_MIN)
 * @buf: buffer
 * @idx: pointer to index
 * @n: number
 * Return: number of chars added
 */
int print_number(char *buf, int *idx, long n)
{
	char tmp[32];
	int i = 0, cnt = 0;
	unsigned long num;

	if (n < 0)
	{
		buf_putc(buf, idx, '-');
		/* convert carefully to avoid overflow */
		num = (unsigned long)(-(n + 1)) + 1;
	}
	else
		num = (unsigned long)n;

	/* convert to digits reverse */
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
 * print_unsigned_num_base - print unsigned number in any base (up to 16)
 * @buf: buffer
 * @idx: pointer to index
 * @n: number
 * @base: base (2,8,10,16)
 * @uppercase: 1 => HEX uses uppercase
 * Return: number of chars added
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
 * print_pointer - print pointer as 0x.... (lowercase hex)
 * @buf: buffer
 * @idx: pointer to index
 * @p: pointer
 * Return: number of chars added
 */
int print_pointer(char *buf, int *idx, void *p)
{
	unsigned long addr = (unsigned long)p;
	int cnt = 0;

	/* print "0x" */
	buf_putc(buf, idx, '0');
	buf_putc(buf, idx, 'x');
	cnt += 2;
	/* print address in hex lowercase */
	cnt += print_unsigned_num_base(buf, idx, addr, 16, 0);
	return (cnt);
}

/**
 * _printf - simplified printf implementation supporting tasks 0..6
 * @format: format string
 * Return: number of characters printed
 *
 * Supported conversions:
 *   %c, %s, %%, %d, %i, %b (binary), %u, %o, %x, %X, %p
 */
int _printf(const char *format, ...)
{
	va_list ap;
	char buf[BUFSIZE];
	int idx = 0, total = 0;
	const char *p;
	char ch;
	int added;

	if (!format)
		return (-1);

	va_start(ap, format);
	for (p = format; *p != '\0'; p++)
	{
		if (*p != '%')
		{
			buf_putc(buf, &idx, *p);
			total++;
			continue;
		}
		/* handle specifier */
		p++;
		if (*p == '\0')
		{
			/* stray % at end -> treat as error */
			va_end(ap);
			return (-1);
		}
		switch (*p)
		{
			case 'c':
				ch = (char)va_arg(ap, int);
				buf_putc(buf, &idx, ch);
				total++;
				break;
			case 's':
			{
				const char *s = va_arg(ap, char *);
				if (!s)
					s = "(null)";
				/* append string */
				for (; *s; s++)
				{
					buf_putc(buf, &idx, *s);
					total++;
				}
				break;
			}
			case '%':
				buf_putc(buf, &idx, '%');
				total++;
				break;
			case 'd':
			case 'i':
			{
				int val = va_arg(ap, int);
				added = print_number(buf, &idx, (long)val);
				total += (added ? added : 0);
				break;
			}
			case 'b':
			{
				unsigned int v = va_arg(ap, unsigned int);
				added = print_unsigned_num_base(buf, &idx, v, 2, 0);
				total += (added ? added : 0);
				break;
			}
			case 'u':
			{
				unsigned int v = va_arg(ap, unsigned int);
				added = print_unsigned_num_base(buf, &idx, v, 10, 0);
				total += (added ? added : 0);
				break;
			}
			case 'o':
			{
				unsigned int v = va_arg(ap, unsigned int);
				added = print_unsigned_num_base(buf, &idx, v, 8, 0);
				total += (added ? added : 0);
				break;
			}
			case 'x':
			{
				unsigned int v = va_arg(ap, unsigned int);
				added = print_unsigned_num_base(buf, &idx, v, 16, 0);
				total += (added ? added : 0);
				break;
			}
			case 'X':
			{
				unsigned int v = va_arg(ap, unsigned int);
				added = print_unsigned_num_base(buf, &idx, v, 16, 1);
				total += (added ? added : 0);
				break;
			}
			case 'p':
			{
				void *ptr = va_arg(ap, void *);
				/* if NULL, printf prints (nil) on some systems; we mimic common behaviour */
				if (!ptr)
				{
					const char *nil = "(nil)";
					buf_append(buf, &idx, nil, 5);
					total += 5;
				}
				else
				{
					added = print_pointer(buf, &idx, ptr);
					total += (added ? added : 0);
				}
				break;
			}
			default:
				/* unknown specifier: print '%' and the char (like standard printf prints the % and then the letter) */
				buf_putc(buf, &idx, '%');
				buf_putc(buf, &idx, *p);
				total += 2;
				break;
		}
	}
	/* flush remaining buffer */
	flush_buffer(buf, &idx);
	va_end(ap);
	return (total);
}

