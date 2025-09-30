#include "main.h"

/**
 * print_s - prints a string
 * @val: argument list
 * Return: length of string printed
 */
int print_s(va_list val)
{
    char *s;
    int i;

    s = va_arg(val, char *);
    if (s == NULL)
        s = "(null)";

    for (i = 0; s[i] != '\0'; i++)
        _putchar(s[i]);

    return (i);
}
