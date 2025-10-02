#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * handle_char - Handles the %c format specifier
 * @args: Argument list containing the character
 *
 * Return: Number of characters printed
 */
int handle_char(va_list args)
{
	char c = va_arg(args, int);

	return (_putchar(c));
}

/**
 * handle_string - Handles the %s format specifier
 * @args: Argument list containing the string
 *
 * Return: Number of characters printed
 */
int handle_string(va_list args)
{
	int count = 0;
	char *str = va_arg(args, char *);

	if (!str)
		str = "(null)";

	while (*str)
	{
		count += _putchar(*str);
		str++;
	}
	return (count);
}

/**
 * handle_percent - Handles the %% format specifier
 *
 * Return: Number of characters printed
 */
int handle_percent(void)
{
	return (_putchar('%'));
}

/**
 * handle_int - Handles %d and %i format specifiers
 * @args: Argument list containing the integer
 *
 * Return: Number of characters printed
 */
int handle_int(va_list args)
{
	int n = va_arg(args, int);
	unsigned int num;
	int count = 0;

	if (n < 0)
	{
		count += _putchar('-');
		num = -n;
	}
	else
	{
		num = n;
	}

	if (num / 10)
		count += handle_int_num(num / 10);

	count += _putchar((num % 10) + '0');

	return (count);
}

/**
 * handle_int_num - helper for handle_int (recursive printing)
 * @n: number to print
 *
 * Return: number of chars printed
 */
int handle_int_num(unsigned int n)
{
	int count = 0;

	if (n / 10)
		count += handle_int_num(n / 10);

	count += _putchar((n % 10) + '0');

	return (count);
}

/**
 * _printf - Produces output according to a format
 * @format: Format string containing specifiers
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	int count = 0;
	va_list args;

	if (!format)
		return (-1);

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c')
				count += handle_char(args);
			else if (*format == 's')
				count += handle_string(args);
			else if (*format == '%')
				count += handle_percent();
			else if (*format == 'd' || *format == 'i')
				count += handle_int(args);
			else
			{
				count += _putchar('%');
				count += _putchar(*format);
			}
		}
		else
		{
			count += _putchar(*format);
		}
		format++;
	}
	va_end(args);

	return (count);
}

