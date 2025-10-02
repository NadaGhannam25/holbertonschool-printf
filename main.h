#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <limits.h>

/* Core printf */
int _printf(const char *format, ...);

/* Basic helpers */
int _putc(char c);
int _puts(const char *s);
int _puts_number(long n, int base, int uppercase);

/* Extra helpers */
int handle_flags(char flag, long *num, int is_signed);
int handle_length(char length, va_list *ap, char sp);

#endif

