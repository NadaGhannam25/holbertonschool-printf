#include "main.h"

int _putchar(char c)
{
    return write(1, &c, 1);
}

int _putstr(char *s)
{
    int count = 0;

    if (!s)
        s = "(null)";
    while (*s)
    {
        if (_putchar(*s++) < 0)
            return -1;
        count++;
    }
    return count;
}
