#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

/**
 * struct format - Struct for specifiers
 * @ph: the format specifier
 * @function: the function associated
 */
typedef struct format
{
    char *ph;
    int (*function)(va_list);
} convert;

int _putchar(char c);
int _printf(const char *format, ...);
int print_c(va_list val);
int print_s(va_list val);
int print_i(va_list args);
int print_d(va_list args);
int print_37(void);

#endif

