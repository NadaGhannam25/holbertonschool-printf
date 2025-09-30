#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

/* Print functions */
int _putchar(char c);
int _printf(const char *format, ...);
int print_c(va_list val);
int print_s(va_list val);
int print_i(va_list args);
int print_d(va_list args);

#endif /* MAIN_H */

