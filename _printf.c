#include "main.h"

/**
 * _printf - simplified printf
 * @format: format string
 * Return: characters printed
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
			/* call parser */
			/* code to select conversion, flags, length modifiers */
			/* for simplicity we call _puts_number or other helpers */
			/* This is where flags, lengths, %S, %p are handled */
			/* Placeholder call example: */
			count += _puts_number(va_arg(ap, int), 10, 0);
			i++;
		}
	}
	va_end(ap);
	return (count);
}

