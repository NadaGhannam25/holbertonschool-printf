#include "main.h"

/**
 * _puts - write a C string to stdout
 * @s: string (prints "(null)" if s is NULL)
 *
 * Return: number of bytes written
 */
static int _puts(const char *s)
{
	int n = 0;

	if (!s)
		s = "(null)";
	while (s[n])
		n++;
	if (n)
		write(1, s, n);
	return (n);
}

/**
 * _putc - write one character to stdout
 * @c: character
 *
 * Return: 1 on success
 */
static int _putc(char c)
{
	return (write(1, &c, 1) == 1 ? 1 : 0);
}

/**
 * _putnbr - print integer
 * @n: number
 *
 * Return: number of characters printed
 */
static int _putnbr(int n)
{
	unsigned int num;
	int count = 0;

	if (n < 0)
	{
		count += _putc('-');
		num = -n;
	}
	else
		num = n;

	if (num / 10)
		count += _putnbr(num / 10);

	count += _putc((num % 10) + '0');
	return (count);
}

/**
 * _putnbr_base - print unsigned int in any base
 * @n: number
 * @base: base (e.g., 2, 8, 10, 16)
 * @uppercase: flag for uppercase hex
 *
 * Return: number of characters printed
 */
static int _putnbr_base(unsigned int n, int base, int uppercase)
{
	char buffer[32];
	char *digits;
	int i = 0, count = 0;

	digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

	if (n == 0)
		return (_putc('0'));

	while (n > 0)
	{
		buffer[i++] = digits[n % base];
		n /= base;
	}

	while (i > 0)
		count += _putc(buffer[--i]);

	return (count);
}

/**
 * print_conv - handle one conversion specifier
 * @sp: specifier character
 * @ap: address of the variadic list
 *
 * Return: number of chars printed for this specifier
 */
static int print_conv(char sp, va_list *ap)
{
	if (sp == 'c')
		return (_putc((char)va_arg(*ap, int)));
	if (sp == 's')
		return (_puts(va_arg(*ap, char *)));
	if (sp == '%')
		return (_putc('%'));
	if (sp == 'd' || sp == 'i')
		return (_putnbr(va_arg(*ap, int)));
	if (sp == 'b')
		return (_putnbr_base(va_arg(*ap, unsigned int), 2, 0));
	if (sp == 'u')
		return (_putnbr_base(va_arg(*ap, unsigned int), 10, 0));
	if (sp == 'o')
		return (_putnbr_base(va_arg(*ap, unsigned int), 8, 0));
	if (sp == 'x')
		return (_putnbr_base(va_arg(*ap, unsigned int), 16, 0));
	if (sp == 'X')
		return (_putnbr_base(va_arg(*ap, unsigned int), 16, 1));

	/* unknown specifier: print '%' then the char */
	return (_putc('%') + _putc(sp));
}

/**
 * _printf - produces output according to a format
 * @format: format string
 *
 * Return: number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list ap;
	int count = 0, i = 0;

	if (!format)
		return (-1);

	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
			count += _putc(format[i++]);
		else
		{
			i++;
			if (!format[i])
			{
				va_end(ap);
				return (-1);
			}
			count += print_conv(format[i++], &ap);
		}
	}
	va_end(ap);
	return (count);
}
