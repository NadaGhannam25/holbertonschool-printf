#include "main.h"

/**
 * _putchar - writes one character to stdout
 * @c: character
 *
 * Return: 1 on success
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string
 * @s: string
 *
 * Return: number of chars printed
 */
int _puts(char *s)
{
	int i = 0;

	if (!s)
		s = "(null)";
	while (s[i])
	{
		_putchar(s[i]);
		i++;
	}
	return (i);
}

/**
 * convert - converts number to string in base
 * @num: number
 * @base: base
 * @lower: 1 for lowercase, 0 for uppercase
 *
 * Return: pointer to string
 */
char *convert(unsigned long int num, int base, int lower)
{
	static char buffer[50];
	char *digits;
	char *ptr = &buffer[49];

	digits = lower ? "0123456789abcdef" : "0123456789ABCDEF";
	*ptr = '\0';

	do {
		*--ptr = digits[num % base];
		num /= base;
	} while (num);

	return (ptr);
}

