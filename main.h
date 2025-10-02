#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stddef.h>

int _printf(const char *format, ...);


int _putc(char c);
int _puts(const char *s);
int _puts_number(long n, int base, int uppercase, int flags);


#define FLAG_PLUS 1
#define FLAG_SPACE 2
#define FLAG_HASH 4

#endif

