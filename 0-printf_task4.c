#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
/* low-level helpers */
static int _putchar(char c)
{
return write(1, &c, 1) == 1 ? 1 : -1;
}
static int _putstr(const char *s)
{
int len;
if (!s)
s = "(null)";
len = strlen(s);
if (write(1, s, len) != len)
return -1;
return len;
}
/* Convert unsigned long int to string in any base */
static char *ultoa_base(unsigned long int value, unsigned int base, int uppercase)
{
char buf[65];
const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
int i = 0;
int j;
char *res;
unsigned long int v = value;
if (v == 0)
{
res = malloc(2);
if (!res) return NULL;
res[0] = '0'; res[1] = '\0';
return res;
}
while (v > 0)
{
buf[i++] = digits[v % base];
v /= base;
}
res = malloc(i + 1);
if (!res) return NULL;
for (j = 0; j < i; j++)
res[j] = buf[i - j - 1];
res[i] = '\0';
return res;
}
static int print_unsigned_base_long(unsigned long int val, unsigned int base, int uppercase)
{
char *s = ultoa_base(val, base, uppercase);
int printed;
if (!s) return -1;
printed = _putstr(s);
free(s);
return printed;
}
int _printf(const char *format, ...)
{
va_list ap;
int total = 0, res;
size_t i;
unsigned long int lval;
if (!format) return -1;
va_start(ap, format);
for (i = 0; format[i]; i++)
{
if (format[i] != '%')
{
res = _putchar(format[i]);
if (res < 0) { va_end(ap); return -1; }
total += res;
continue;
}
i++;
if (!format[i]) { va_end(ap); return -1; }
switch (format[i])
{
case 'c':
res = _putchar((char)va_arg(ap, int));
break;
case 's':
res = _putstr(va_arg(ap, char *));
break;
case '%':
res = _putchar('%');
break;
case 'u':
lval = va_arg(ap, long int);
if ((long int)lval < 0)
lval = (unsigned long int)lval;
res = print_unsigned_base_long(lval, 10, 0);
break;
case 'o':
lval = va_arg(ap, long int);
if ((long int)lval < 0)
lval = (unsigned long int)lval;
res = print_unsigned_base_long(lval, 8, 0);
break;
case 'x':
lval = va_arg(ap, long int);
if ((long int)lval < 0)
lval = (unsigned long int)lval;
res = print_unsigned_base_long(lval, 16, 0);
break;
case 'X':
lval = va_arg(ap, long int);
if ((long int)lval < 0)
lval = (unsigned long int)lval;
res = print_unsigned_base_long(lval, 16, 1);
break;
default:
res = _putchar('%');
if (res >= 0) total += res;
res = _putchar(format[i]);
break;
}
if (res < 0) { va_end(ap); return -1; }
total += res;
}
va_end(ap);
return total;
}
