#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

int _printf(const char *format, ...);
int _putc(char c);
int _puts(const char *s);
int _puts_number(long n, int base, int uppercase);

#endif

