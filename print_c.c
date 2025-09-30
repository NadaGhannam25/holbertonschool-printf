#include "main.h"

/**
 * print_c - prints a character
 * @val: argument list
 * Return: 1
 */
int print_c(va_list val)
{
    char c = va_arg(val, int);
    _putchar(c);
    return (1);
}
