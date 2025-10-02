#include "main.h"
#include <stdarg.h>
#include <string.h>

/**
 * _printf - prints formatted output
 * @format: format string
 * Return: number of chars printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, printed = 0, precision = -1;

	va_start(args, format);

	while (format && format[i])
	{
		if (format[i] != '%')
		{
			printed += _putc(format[i]);
			i++;
			continue;
		}

		i++;
		precision = -1;

		/* check precision */
		if (format[i] == '.')
		{
			i++;
			precision = 0;
			while (format[i] >= '0' && format[i] <= '9')
			{
				precision = precision * 10 + (format[i] - '0');
				i++;
			}
		}

		switch (format[i])
		{
			case 'c':
				printed += _putc(va_arg(args, int));
				break;
			case 's':
				printed += print_string(va_arg(args, char *), precision);
				break;
			case 'S':
				printed += print_custom_S(va_arg(args, char *));
				break;
			case 'd':
			case 'i':
				printed += print_number(va_arg(args, int), 10, 0, 0, precision);
				break;
			case 'u':
				printed += print_number(va_arg(args, unsigned int), 10, 1, 0, precision);
				break;
			case 'o':
				printed += print_number(va_arg(args, unsigned int), 8, 1, 0, precision);
				break;
			case 'x':
				printed += print_number(va_arg(args, unsigned int), 16, 1, 0, precision);
				break;
			case 'X':
				printed += print_number(va_arg(args, unsigned int), 16, 1, 1, precision);
				break;
			case 'p':
				printed += print_pointer(va_arg(args, void *));
				break;
			case '%':
				printed += _putc('%');
				break;
		}
		i++;
	}

	va_end(args);
	return (printed);
}

