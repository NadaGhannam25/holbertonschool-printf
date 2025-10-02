#include "main.h"
#include <stdarg.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * flush_buffer - writes the buffer to stdout and resets index
 * @buf: buffer array
 * @index: pointer to current index in buffer
 *
 * Return: number of characters written
 */
static int flush_buffer(char *buf, int *index)
{
	int written = 0;

	if (*index > 0)
	{
		written = write(1, buf, *index);
		*index = 0;
	}
	return (written);
}

/**
 * _putc_buffered - adds a character to buffer, flushes if full
 * @c: character to write
 * @buf: buffer array
 * @index: pointer to current index in buffer
 *
 * Return: number of characters written (0 or BUFFER_SIZE)
 */
static int _putc_buffered(char c, char *buf, int *index)
{
	int count = 0;

	buf[(*index)++] = c;

	if (*index == BUFFER_SIZE)
		count = flush_buffer(buf, index);

	return (count);
}

/**
 * print_conv - handles a single conversion specifier
 * @sp: conversion specifier character
 * @ap: address of the variadic list
 * @buf: buffer array
 * @index: pointer to current index in buffer
 *
 * Return: number of characters written directly
 */
static int print_conv(char sp, va_list *ap, char *buf, int *index)
{
	int count = 0;

	if (sp == 'c')
		count += _putc_buffered((char)va_arg(*ap, int), buf, index);
	else if (sp == 's')
	{
		char *s = va_arg(*ap, char *);
		if (!s)
			s = "(null)";
		while (*s)
			count += _putc_buffered(*s++, buf, index);
	}
	else if (sp == '%')
		count += _putc_buffered('%', buf, index);
	else if (sp == 'd' || sp == 'i')
		count += _puts_number(va_arg(*ap, int), 10, 0, buf, index);
	else if (sp == 'u')
		count += _puts_number(va_arg(*ap, unsigned int), 10, 0, buf, index);
	else if (sp == 'o')
		count += _puts_number(va_arg(*ap, unsigned int), 8, 0, buf, index);
	else if (sp == 'x')
		count += _puts_number(va_arg(*ap, unsigned int), 16, 0, buf, index);
	else if (sp == 'X')
		count += _puts_number(va_arg(*ap, unsigned int), 16, 1, buf, index);
	else if (sp == 'b')
		count += _puts_number(va_arg(*ap, unsigned int), 2, 0, buf, index);
	else
	{
		count += _putc_buffered('%', buf, index);
		count += _putc_buffered(sp, buf, index);
	}

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
	int count = 0, i = 0, buf_index = 0;
	char buffer[BUFFER_SIZE];

	if (!format)
		return (-1);

	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
			count += _putc_buffered(format[i++], buffer, &buf_index);
		else
		{
			i++;
			if (!format[i])
			{
				va_end(ap);
				return (-1);
			}
			count += print_conv(format[i++], &ap, buffer, &buf_index);
		}
	}
	/* flush any remaining chars */
	count += flush_buffer(buffer, &buf_index);

	va_end(ap);
	return (count);
}

