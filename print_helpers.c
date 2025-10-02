#include "main.h"
#include <string.h>

/* print a single char */
int _putc(char c)
{
	return (write(1, &c, 1));
}

/* print string */
int _puts(const char *s)
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

/* print number with base and precision */
int print_number(long n, int base, int is_unsigned, int is_upper, int prec)
{
	char buffer[65], *digits;
	int i = 0, printed = 0;
	unsigned long num;

	if (is_upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";

	if (!is_unsigned && n < 0)
	{
		printed += _putc('-');
		num = -n;
	}
	else
		num = (unsigned long)n;

	do {
		buffer[i++] = digits[num % base];
		num /= base;
	} while (num != 0);

	while (i < prec)
	{
		printed += _putc('0');
		i++;
	}

	while (--i >= 0)
		printed += _putc(buffer[i]);

	return (printed);
}

/* print string with precision */
int print_string(char *s, int prec)
{
	int len = 0, i;

	if (!s)
		s = "(null)";

	for (i = 0; s[i] && (prec < 0 || i < prec); i++)
		len += _putc(s[i]);

	return (len);
}

/* print pointer */
int print_pointer(void *p)
{
	unsigned long addr = (unsigned long)p;
	int printed = 0;

	printed += _puts("0x");
	printed += print_number(addr, 16, 1, 0, 0);

	return (printed);
}

/* print %S custom */
int print_custom_S(char *s)
{
	int printed = 0, i = 0;
	unsigned char c;

	if (!s)
		s = "(null)";

	while (s[i])
	{
		c = s[i];
		if (c < 32 || c >= 127)
		{
			printed += _putc('\\');
			printed += _putc('x');
			printed += print_number(c, 16, 1, 1, 2);
		}
		else
			printed += _putc(c);
		i++;
	}
	return (printed);
}

