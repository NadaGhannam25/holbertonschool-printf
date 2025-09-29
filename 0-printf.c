
#include "main.h"
/**
* _putchar - write single char to stdout
*/
static int _putchar(char c)
{
if (write(1, &c, 1) != 1)
return -1;
return 1;
}
/**
* _putstr - write string to stdout, treat NULL as "(null)"
*/
static int _putstr(char *s)
{
unsigned int len = 0;
if (s == NULL)
s = "(null)";
while (s[len])
len++;
if (len == 0)
return 0;
if (write(1, s, len) != (ssize_t)len)
return -1;
return (int)len;
}
/**
 * _printf - simplified printf supporting %c, %s and %%
 * @format: format string
 * Return: number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
va_list ap;
int count = 0;
unsigned int i;
int res;
if (format == NULL)
return -1;
va_start(ap, format);
for (i = 0; format[i] != '\0'; i++)
{
if (format[i] != '%')
{
res = _putchar(format[i]);
if (res < 0) { va_end(ap); return -1; }
count += res;
continue;
}
/* got '%' */
i++;
if (format[i] == '\0')
{
va_end(ap);
return -1;
}
if (format[i] == 'c')
{
char c = (char)va_arg(ap, int);
res = _putchar(c);
if (res < 0) { va_end(ap); return -1; }
count += res;
}
else if (format[i] == 's')
{
char *s = va_arg(ap, char *);
res = _putstr(s);
if (res < 0) { va_end(ap); return -1; }
count += res;
}
else if (format[i] == '%')
{
res = _putchar('%');
if (res < 0) { va_end(ap); return -1; }
count += res;
}
else
{
/* unsupported -> print '%' then the char */
res = _putchar('%');
if (res < 0) { va_end(ap); return -1; }
count += res;
res = _putchar(format[i]);
if (res < 0) { va_end(ap); return -1; }
count += res;
}
}
va_end(ap);
return count;
}
