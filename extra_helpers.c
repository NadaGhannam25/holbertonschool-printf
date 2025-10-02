#include "main.h"
#include <string.h>

/* handle precision for numbers and strings */
int handle_precision(char *s, int prec, int is_number)
{
	int len = 0, i = 0, printed = 0;

	if (!s)
		s = "(null)";

	len = strlen(s);

	if (is_number)
	{
		while (len < prec)
		{
			printed += _putc('0');
			len++;
		}
	}

	for (i = 0; i < len && (!is_number || i < len); i++)
	{
		if (!is_number && prec >= 0 && i >= prec)
			break;
		printed += _putc(s[i]);
	}

	return (printed);
}

