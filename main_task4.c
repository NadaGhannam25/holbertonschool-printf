#include "main.h"
#include <limits.h>

int main(void)
{
unsigned long int res, l;

_printf("%u\n", 1024);
_printf("%u\n", -1024);
_printf("%u\n", 0);
_printf("%u\n", UINT_MAX);

l = (unsigned long int)UINT_MAX + 1024;
_printf("%u\n", l);

_printf("There is %u bytes in %u KB\n", 1024, 1);

res = (unsigned long int)INT_MAX * 2;
_printf("%u + %u = %u\n", INT_MAX, INT_MAX, res);

_printf("%o\n", 1024);
_printf("%o\n", -1024);
_printf("%o\n", 0);
_printf("%o\n", UINT_MAX);
_printf("%o\n", l);

_printf("%x\n", 1024);
_printf("%x\n", -1024);
_printf("%x\n", 0);
_printf("%x\n", UINT_MAX);
_printf("%x\n", l);

_printf("%X\n", 1024);
_printf("%X\n", -1024);
_printf("%X\n", 0);
_printf("%X\n", UINT_MAX);
_printf("%X\n", l);

return 0;
}
