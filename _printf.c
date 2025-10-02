#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * write_char - prints a single character to stdout
 * @c: character to print
 *
 * Return: 1 on success, 0 on failure
 */
static int write_char(char c)
{
	if (write(1, &c, 1) != 1)
		return (0);
	return (1);
}

/**
 * write_str - prints a string to stdout
 * @str: string to print
 *
 * Return: number of characters printed
 */
static int write_str(const char *str)
{
	int i = 0;

	if (!str)
		str = "(null)";

	while (str[i])
	{
		write_char(str[i]);
		i++;
	}
	return i;
}

/**
 * handle_format - handles a single format specifier
 * @fmt: format specifier character
 * @args: variadic argument list
 *
 * Return: number of characters printed
 */
static int handle_format(char fmt, va_list args)
{
	if (fmt == 'c')
		return write_char((char)va_arg(args, int));
	if (fmt == 's')
		return write_str(va_arg(args, char *));
	if (fmt == '%')
		return write_char('%');

	/* unknown specifier: print '%' then the char */
	write_char('%');
	return 1 + write_char(fmt);
}

/**
 * _printf - simplified printf function
 * @format: format string
 *
 * Return: number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list args;
	int total = 0;
	int i = 0;

	if (!format)
		return -1;

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!format[i])
			{
				va_end(args);
				return -1;
			}
			total += handle_format(format[i], args);
		}
		else
			total += write_char(format[i]);
		i++;
	}
	va_end(args);
	return total;
}

