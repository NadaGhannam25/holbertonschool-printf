#include "main.h"

/**
 * handle_specifier - choose the right function for a format specifier
 * @spec: the specifier character
 * @ap: list of arguments
 * @buf: buffer
 * @idx: buffer index
 *
 * Return: number of chars printed
 */
int handle_specifier(char spec, va_list ap, char *buf, int *idx)
{
	int count = 0;
	char *s;

	switch (spec)
	{
	case 'c':
		return (buf_putc(buf, idx, (char)va_arg(ap, int)));
	case 's':
		s = va_arg(ap, char *);
		if (!s)
			s = "(null)";
		while (*s)
			buf_putc(buf, idx, *s++), count++;
		return (count);
	case '%':
		return (buf_putc(buf, idx, '%'));
	case 'd':
	case 'i':
		return (print_number(buf, idx, (long)va_arg(ap, int)));
	case 'b':
		return (print_unsigned_num_base(buf, idx,
			va_arg(ap, unsigned int), 2, 0));
	case 'u':
		return (print_unsigned_num_base(buf, idx,
			va_arg(ap, unsigned int), 10, 0));
	case 'o':
		return (print_unsigned_num_base(buf, idx,
			va_arg(ap, unsigned int), 8, 0));
	case 'x':
		return (print_unsigned_num_base(buf, idx,
			va_arg(ap, unsigned int), 16, 0));
	case 'X':
		return (print_unsigned_num_base(buf, idx,
			va_arg(ap, unsigned int), 16, 1));
	case 'p':
	{
		void *ptr = va_arg(ap, void *);
		if (!ptr)
			return (buf_append(buf, idx, "(nil)", 5));
		return (print_pointer(buf, idx, ptr));
	}
	default:
		buf_putc(buf, idx, '%');
		buf_putc(buf, idx, spec);
		return (2);
	}
}

/**
 * _printf - simplified printf implementation
 * @format: format string
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list ap;
	char buf[BUFSIZE];
	int idx = 0, total = 0;
	const char *p;

	if (!format)
		return (-1);

	va_start(ap, format);
	for (p = format; *p; p++)
	{
		if (*p == '%')
		{
			p++;
			if (!*p)
				return (-1);
			total += handle_specifier(*p, ap, buf, &idx);
		}
		else
		{
			buf_putc(buf, &idx, *p);
			total++;
		}
	}
	flush_buffer(buf, &idx);
	va_end(ap);
	return (total);
}

