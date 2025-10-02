#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int _printf(const char *format, ...);

int _putchar(char c);
int _puts(char *s);
char *convert(unsigned long int num, int base, int lowercase);

int print_int(va_list args);
int print_unsigned(va_list args);
int print_octal(va_list args);
int print_hex(va_list args, int lower);

#endif
