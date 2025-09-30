#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>

/* Print functions */
int print_HEX(unsigned int num);
int print_HEX_extra(unsigned int num);
int print_bin(unsigned int num);
int print_exc_string(const char *s);
int print_hex(unsigned int num);
int print_hex_extra(unsigned int num);
int print_oct(unsigned int num);
int print_pointer(void *ptr);
int print_rot13(const char *s);
int print_srev(const char *s);
int print_str(const char *s);
int print_uns(unsigned int num);

#endif /* MAIN_H */

