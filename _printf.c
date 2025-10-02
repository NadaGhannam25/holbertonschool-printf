#include "main.h"
#include <stdarg.h>
#include <limits.h>

/* forward declaration */
static int print_conv(char sp, va_list *ap);

/**
 * _printf - formatted output with flags +, space, #
 * @format: format string
 * Return: number of chars printed or -1
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
			count += _putc_buffered(format[i++]);
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
	flush_buffer();
	va_end(ap);
	return (count);
}

/**
 * print_conv - handle conversion specifier with flags
 * @sp: conversion specifier
 * @ap: variadic list
 * Return: number of chars printed
 */
static int print_conv(char sp, va_list *ap)
{
	int count = 0;
	long n;
	unsigned int num;
	char flag_plus = 0, flag_space = 0, flag_hash = 0;
	char c;

	/* check for flags */
	while (sp == '+' || sp == ' ' || sp == '#')
	{
		if (sp == '+')
			flag_plus = 1;
		else if (sp == ' ')
			flag_space = 1;
		else if (sp == '#')
			flag_hash = 1;
		sp = va_arg(*ap, int);
	}

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
		if (n < 0)
		{
			count += _putc_buffered('-');
			n = -n;
		}
		else if (flag_plus)
			count += _putc_buffered('+');
		else if (flag_space)
			count += _putc_buffered(' ');
		count += _puts_number(n, 10, 0);
		break;
	case 'u':
		num = va_arg(*ap, unsigned int);
		count += _puts_number(num, 10, 0);
		break;
	case 'o':
		num = va_arg(*ap, unsigned int);
		if (flag_hash && num != 0)
			count += _putc_buffered('0');
		count += _puts_number(num, 8, 0);
		break;
	case 'x':
		num = va_arg(*ap, unsigned int);
		if (flag_hash && num != 0)
		{
			count += _putc_buffered('0');
			count += _putc_buffered('x');
		}
		count += _puts_number(num, 16, 0);
		break;
	case 'X':
		num = va_arg(*ap, unsigned int);
		if (flag_hash && num != 0)
		{
			count += _putc_buffered('0');
			count += _putc_buffered('X');
		}
		count += _puts_number(num, 16, 1);
		break;
	case 'b':
		num = va_arg(*ap, unsigned int);
		count += _puts_number(num, 2, 0);
		break;
	default:
		count += _putc_buffered('%');
		count += _putc_buffered(sp);
		break;
	}

	return (count);
}

