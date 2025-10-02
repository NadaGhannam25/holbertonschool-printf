#include "main.h"

/**
 * _printf - produces output according to a format
 * @format: character string
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, count = 0;

	if (!format)
		return (-1);

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!format[i])
				return (-1);

			if (format[i] == 'd' || format[i] == 'i')
				count += print_int(args);
			else if (format[i] == 'u')
				count += print_unsigned(args);
			else if (format[i] == 'o')
				count += print_octal(args);
			else if (format[i] == 'x')
				count += print_hex(args, 1);
			else if (format[i] == 'X')
				count += print_hex(args, 0);
			else if (format[i] == 'c')
				count += _putchar(va_arg(args, int));
			else if (format[i] == 's')
				count += _puts(va_arg(args, char *));
			else if (format[i] == '%')
				count += _putchar('%');
			else
				count += _putchar(format[i]);
		}
		else
			count += _putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

