#include "main.h"

/**
 * print_int - prints integer
 * @args: argument list
 *
 * Return: number of chars printed
 */
int print_int(va_list args)
{
	long n = va_arg(args, int);
	char *str;
	int count = 0;

	if (n < 0)
	{
		count += _putchar('-');
		n = -n;
	}
	str = convert(n, 10, 0);
	count += _puts(str);
	return (count);
}

/**
 * print_unsigned - prints unsigned int
 * @args: argument list
 *
 * Return: number of chars printed
 */
int print_unsigned(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);
	char *str = convert(n, 10, 0);

	return (_puts(str));
}

/**
 * print_octal - prints unsigned int in octal
 * @args: argument list
 *
 * Return: number of chars printed
 */
int print_octal(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);
	char *str = convert(n, 8, 0);

	return (_puts(str));
}

/**
 * print_hex - prints unsigned int in hex
 * @args: argument list
 * @lower: 1 for lowercase, 0 for uppercase
 *
 * Return: number of chars printed
 */
int print_hex(va_list args, int lower)
{
	unsigned int n = va_arg(args, unsigned int);
	char *str = convert(n, 16, lower);

	return (_puts(str));
}

