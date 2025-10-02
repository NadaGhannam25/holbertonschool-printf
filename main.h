#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>

#define BUFSIZE 1024

int _printf(const char *format, ...);

/* buffer helpers */
int flush_buffer(char *buf, int *idx);
int buf_append(char *buf, int *idx, const char *s, int len);
int buf_putc(char *buf, int *idx, char c);

/* conversion helpers */
int print_number(char *buf, int *idx, long n);
int print_unsigned_num_base(char *buf, int *idx, unsigned long n,
                            int base, int uppercase);
int print_pointer(char *buf, int *idx, void *p);

#endif /* MAIN_H */

