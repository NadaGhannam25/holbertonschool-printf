#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

/* _printf main function */
int _printf(const char *format, ...);

/* Basic print helpers */
int _putc(char c);
int _puts(const char *s);
int _puts_number(long n, int base, int uppercase);

/* Extended helpers */
int _print_S(const char *s);
int _print_pointer(void *p);

/* Flag helpers */
int _handle_flags(char flag, long num, int base, int uppercase);

/* Length modifiers helpers */
long _get_long(va_list *ap);
short _get_short(va_list *ap);

#endif

