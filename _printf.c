 #include "main.h"
#include <stdarg.h>

/**
 * print_conv - handles a single conversion specifier
 * @sp: conversion specifier character
 * @ap: address of the variadic list
 *
 * Return: number of characters printed
 */
static int print_conv(char sp, va_list *ap)
{
	int count = 0;

	if (sp == 'c')
		count = _putc((char)va_arg(*ap, int));
	else if (sp == 's')
		count = _puts(va_arg(*ap, char *));
	else if (sp == '%')
		count = _putc('%');
	else if (sp == 'd' || sp == 'i')
		count = _puts_number(va_arg(*ap, int), 10, 0);
	else if (sp == 'u')
		count = _puts_number(va_arg(*ap, unsigned int), 10, 0);
	else if (sp == 'o')
		count = _puts_number(va_arg(*ap, unsigned int), 8, 0);
	else if (sp == 'x')
		count = _puts_number(va_arg(*ap, unsigned int), 16, 0);
	else if (sp == 'X')
		count = _puts_number(va_arg(*ap, unsigned int), 16, 1);
	else if (sp == 'b')
		count = _puts_number(va_arg(*ap, unsigned int), 2, 0);
	else
		count = _putc('%') + _putc(sp);

	return (count);
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
