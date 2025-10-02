#include "main.h"
#include <stdarg.h>
#include <limits.h>

/**
 * handle_flags - adjust number for +, space, #
 * @flag: flag character
 * @num: number to adjust
 * @is_signed: 1 if signed
 * Return: 0 (placeholder, can integrate with _puts_number)
 */
int handle_flags(char flag, long *num, int is_signed)
{
	(void)num;
	(void)flag;
	(void)is_signed;
	/* يمكن توسعها لاحقًا */
	return (0);
}

/**
 * handle_length - fetch argument by length modifier
 * @length: 'l' or 'h'
 * @ap: pointer to va_list
 * @sp: conversion specifier
 * Return: number of chars printed
 */
int handle_length(char length, va_list *ap, char sp)
{
	long val = 0;
	short sval = 0;
	unsigned long uval = 0;
	unsigned short usval = 0;

	switch (length)
	{
		case 'l':
			if (sp == 'd' || sp == 'i')
				val = va_arg(*ap, long);
			else
				uval = va_arg(*ap, unsigned long);
			return (_puts_number(val ? val : uval, 10, 0));
		case 'h':
			if (sp == 'd' || sp == 'i')
				sval = (short)va_arg(*ap, int);
			else
				usval = (unsigned short)va_arg(*ap, unsigned int);
			return (_puts_number(sval ? sval : usval, 10, 0));
		default:
			if (sp == 'd' || sp == 'i')
				val = va_arg(*ap, int);
			else
				uval = va_arg(*ap, unsigned int);
			return (_puts_number(val ? val : uval, 10, 0));
	}
}

