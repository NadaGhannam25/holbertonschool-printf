#include "main.h"

/**
 * print_pointer - print pointer as hex
 * @buf: buffer
 * @idx: pointer to index
 * @p: pointer
 *
 * Return: chars added
 */
int print_pointer(char *buf, int *idx, void *p)
{
	unsigned long addr = (unsigned long)p;
	int cnt = 0;

	buf_putc(buf, idx, '0');
	buf_putc(buf, idx, 'x');
	cnt += 2;
	cnt += print_unsigned_num_base(buf, idx, addr, 16, 0);
	return (cnt);
}

