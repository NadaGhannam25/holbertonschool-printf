#include "main.h"
#include <stdlib.h>

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
		p++;
		if (*p == '\0')
		{
			va_end(ap);
			return (-1);
		}
		switch (*p)
		{
		case 'c':
			ch = (char)va_arg(ap, int);
			buf_putc(buf, &idx, ch), total++;
			break;
		case 's':
		{
			const char *s = va_arg(ap, char *);
			if (!s)
				s = "(null)";
			while (*s)
				buf_putc(buf, &idx, *s++), total++;
			break;
		}
		case '%':
			buf_putc(buf, &idx, '%'), total++;
			break;
		case 'd': case 'i':
			added = print_number(buf, &idx, (long)va_arg(ap, int));
			total += added;
			break;
		case 'b':
			added = print_unsigned_num_base(buf, &idx,
				va_arg(ap, unsigned int), 2, 0);
			total += added;
			break;
		case 'u':
			added = print_unsigned_num_base(buf, &idx,
				va_arg(ap, unsigned int), 10, 0);
			total += added;
			break;
		case 'o':
			added = print_unsigned_num_base(buf, &idx,
				va_arg(ap, unsigned int), 8, 0);
			total += added;
			break;
		case 'x':
			added = print_unsigned_num_base(buf, &idx,
				va_arg(ap, unsigned int), 16, 0);
			total += added;
			break;
		case 'X':
			added = print_unsigned_num_base(buf, &idx,
				va_arg(ap, unsigned int), 16, 1);
			total += added;
			break;
		case 'p':
		{
			void *ptr = va_arg(ap, void *);
			if (!ptr)
			{
				const char *nil = "(nil)";
				buf_append(buf, &idx, nil, 5);
				total += 5;
			}
			else
			{
				added = print_pointer(buf, &idx, ptr);
				total += added;
			}
			break;
		}
		default:
			buf_putc(buf, &idx, '%');
			buf_putc(buf, &idx, *p);
			total += 2;
			break;
		}
	}
	flush_buffer(buf, &idx);
	va_end(ap);
	return (total);
}

