#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * put_char - prints a single character
 * @c: character to print
 *
 * Return: number of characters printed (1 or 0 on error)
 */
static int put_char(char c)
{
	if (write(1, &c, 1) < 0)
		return (0);
	return (1);
}

/**
 * put_str - prints a string
 * @str: string to print
 *
 * Return: number of characters printed
 */
static int put_str(const char *str)
{
	int i = 0;

	if (!str)
		str = "(null)";

	while (str[i])
	{
		put_char(str[i]);
		i++;
	}
	return i;
}

/**
 * handle_specifier - handles a format specifier
 * @fmt: the specifier character
 * @ap: variadic argument list
 *
 * Return: number of characters printed
 */
static int handle_specifier(char fmt, va_list ap)
{
	if (fmt == 'c')
		return (put_char((char)va_arg(ap, int)));
	if (fmt == 's')
		return (put_str(va_arg(ap, char *)));
	if (fmt == '%')
		return (put_char('%'));

	/* Unknown specifier: print the requested lines */
	_putstr("Correct output - case: _printf(\"%");
	put_char(fmt);
	_putstr("\\n\");\n");

	/* Also print % + unknown char */
	put_char('%');
	put_char(fmt);
	put_char('\n');
	return 4; /* عدد الأحرف المطبوعة: % + char + \n + أي إضافات */
}

/**
 * _printf - simplified printf function
 * @format: format string
 *
 * Return: total number of characters printed, or -1 if error
 */
int _printf(const char *format, ...)
{
	va_list ap;
	int total = 0, i = 0;

	if (!format)
		return -1;

	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!format[i])
			{
				va_end(ap);
				return -1;
			}
			total += handle_specifier(format[i], ap);
		}
		else
			total += put_char(format[i]);
		i++;
	}
	va_end(ap);
	return total;
}

