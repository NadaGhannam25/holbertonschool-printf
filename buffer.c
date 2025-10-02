#include "main.h"

/**
 * flush_buffer - write out buffer to stdout
 * @buf: buffer
 * @idx: pointer to index
 *
 * Return: number of bytes written
 */
int flush_buffer(char *buf, int *idx)
{
	int w;

	if (*idx <= 0)
		return (0);
	w = write(1, buf, *idx);
	*idx = 0;
	return (w);
}

/**
 * buf_putc - append char to buffer, flush if full
 * @buf: buffer
 * @idx: pointer to index
 * @c: char to append
 *
 * Return: 1 on success, -1 on error
 */
int buf_putc(char *buf, int *idx, char c)
{
	int ret;

	buf[*idx] = c;
	(*idx)++;
	if (*idx >= BUFSIZE)
	{
		ret = flush_buffer(buf, idx);
		if (ret < 0)
			return (-1);
	}
	return (1);
}

/**
 * buf_append - append string of len chars to buffer
 * @buf: buffer
 * @idx: pointer to index
 * @s: string
 * @len: length
 *
 * Return: number of chars appended
 */
int buf_append(char *buf, int *idx, const char *s, int len)
{
	int i;

	for (i = 0; i < len; i++)
	{
		if (buf_putc(buf, idx, s[i]) < 0)
			return (-1);
	}
	return (len);
}

