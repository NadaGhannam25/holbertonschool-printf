#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

/* _printf function */
int _printf(const char *format, ...);

/* Helpers */
int _putc(char c);
int _puts(const char *s);
int handle_flags(char *s, char flag);
int handle_precision(char *s, int prec, int is_number);
int print_number(long n, int base, int is_unsigned, int is_upper, int prec);
int print_string(char *s, int prec);
int print_pointer(void *p);
int print_custom_S(char *s);

#endif

