#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

#define BUFFER_SIZE 1024

/**
 * flush_buffer - write contents of buffer to stdout and reset index
 * @buf: buffer array
 * @index: pointer to current index
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
 * _putc_buffered - add a character to buffer; flush if full
 * @c: character to add
 * @buf: buffer array
 * @index: pointer to buffer index
 *
 * Return: number of characters written directly
 */
int _putc_buffered(char c, char *buf, int *index)
{
	int count = 0;

	buf[(*index)++] = c;

	if (*index == BUFFER_SIZE)
		count = flush_buffer(buf, index);

	return (count);
}

/**
 * print_conv - handle one conversion specifier
 * @sp: conversion specifier
 * @ap: variadic arguments
 * @buf: buffer array
 * @index: pointer to buffer index
 *
 * Return: number of characters written
 */
static int print_conv(char sp, va_list *ap, char *buf, int *index)
{
	int count = 0;
	char *s;
	long num;

	switch (sp)
	{
	case 'c':
		count += _putc_buffered((char)va_arg(*ap, int), buf, index);
		break;
	case 's':
		s = va_arg(*ap, char *);
		if (!s)
			s = "(null)";
		while (*s)
			count += _putc_buffered(*s++, buf, index);
		break;
	case '%':
		count += _putc_buffered('%', buf, index);
		break;
	case 'd':
	case 'i':
		num = va_arg(*ap, int);
		count += _puts_number(num, 10, 0, buf, index);
		break;
	case 'u':
		num = va_arg(*ap, unsigned int);
		count += _puts_number(num, 10, 0, buf, index);
		break;
	case 'o':
		num = va_arg(*ap, unsigned int);
		count += _puts_number(num, 8, 0, buf, index);
		break;
	case 'x':
		num = va_arg(*ap, unsigned int);
		count += _puts_number(num, 16, 0, buf, index);
		break;
	case 'X':
		num = va_arg(*ap, unsigned int);
		count += _puts_number(num, 16, 1, buf, index);
		break;
	case 'b':
		num = va_arg(*ap, unsigned int);
		count += _puts_number(num, 2, 0, buf, index);
		break;
	default:
		count += _putc_buffered('%', buf, index);
		count += _putc_buffered(sp, buf, index);
		break;
	}
	return (count);
}

/**
 * _printf - formatted output to stdout using local buffer
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

	/* flush remaining characters */
	count += flush_buffer(buffer, &buf_index);

	va_end(ap);
	return (count);
}


