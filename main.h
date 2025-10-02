#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

int _printf(const char *format, ...);
int _putc_buffered(char c, char *buf, int *index);
int _puts_number(long n, int base, int uppercase, char *buf, int *index);

#endif

