#ifndef MAIN_H
#define MAIN_H

int _printf(const char *format, ...);
int print_char(va_list, int length);
int print_string(va_list, int length);
int handle_mod(va_list, int length);
int print_int(va_list, int length);

typedef struct
{
	char *specifier;
	int (*func)(va_list, int length);
} spec;

#endif /* MAIN_H */
