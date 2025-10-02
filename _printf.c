#include "main.h"
#include <stdarg.h>
#include <limits.h>

/* forward declaration */
static int print_conv(char sp, va_list *ap, int flag_plus, int flag_space, int flag_hash);

/**
 * _printf - formatted output with +, space, #
 * @format: format string
 * Return: chars printed
 */
int _printf(const char *format, ...)
{
	va_list ap;
	int count = 0, i = 0;
	int flag_plus, flag_space, flag_hash;

	if (!format)
		return (-1);

	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
			count += _putc_buffered(format[i++]);
		else
		{
			i++;
			flag_plus = flag_space = flag_hash = 0;

			/* read flags */
			while (format[i] == '+' || format[i] == ' ' || format[i] == '#')
			{
				if (format[i] == '+')
					flag_plus = 1;
				else if (format[i] == ' ')
					flag_space = 1;
				else if (format[i] == '#')
					flag_hash = 1;
				i++;
			}

			if (!format[i])
			{
				va_end(ap);
				return (-1);
			}

			count += print_conv(format[i++], &ap, flag_plus, flag_space, flag_hash);
		}
	}
	flush_buffer();
	va_end(ap);
	return (count);
}

/**
 * print_conv - handle conversion specifiers with flags
 */
static int print_conv(char sp, va_list *ap, int flag_plus, int flag_space, int flag_hash)
{
	int count = 0;
	long n;
	unsigned int num;
	char c;

	switch (sp)
	{
	case 'c':
		c = (char)va_arg(*ap, int);
		count += _putc_buffered(c);
		break;
	case 's':
		count += _puts(va_arg(*ap, char *));
		break;
	case '%':
		count += _putc_buffered('%');
		break;
	case 'd':
	case 'i':
		n = va_arg(*ap, long);
		count += _puts_number(n, 10, 0, flag_plus, flag_space);
		break;
	case 'u':
		num = va_arg(*ap, unsigned int);
		count += _puts_number(num, 10, 0, 0, 0);
		break;
	case 'o':
		num = va_arg(*ap, unsigned int);
		if (flag_hash && num != 0)
			count += _putc_buffered('0');
		count += _puts_number(num, 8, 0, 0, 0);
		break;
	case 'x':
		num = va_arg(*ap, unsigned int);
		if (flag_hash && num != 0)
		{
			count += _putc_buffered('0');
			count += _putc_buffered('x');
		}
		count += _puts_number(num, 16, 0, 0, 0);
		break;
	case 'X':
		num = va_arg(*ap, unsigned int);
		if (flag_hash && num != 0)
		{
			count += _putc_buffered('0');
			count += _putc_buffered('X');
		}
		count += _puts_number(num, 16, 1, 0, 0);
		break;
	case 'b':
		num = va_arg(*ap, unsigned int);
		count += _puts_number(num, 2, 0, 0, 0);
		break;
	default:
		count += _putc_buffered('%');
		count += _putc_buffered(sp);
		break;
	}
	return (count);
}

