#include "main.h"

/**
 * c_spec - prints a character
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed characters
 */
int c_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length)
{
	int printed;
	char z;

	z = va_arg(arg, int);
	printed = write_char(z, buff, flags, width, precision, length);

	return (printed);
}


/**
 * int_spec - prints integer value
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of character printed
 */
int int_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length)
{
	unsigned long int v;
	long int k;
	int num = 0, i = LOCAL_BUFF - 2;

	k = va_arg(arg, long int);
	k = size_Convert(k, length);
	if (k == 0)
	{
		buff[i--] = '0';
	}
	buff[LOCAL_BUFF - 1] = '\0';
	v = (unsigned long int)k;
	if (k < 0)
	{
		v = (unsigned long int)((-1) * k);
		num = 1;
	}
	for (; v > 0; v /= 10)
	{
		buff[i--] = (v % 10) + '0';
	}
	i++;
	return (write_number(num, i, buff, flags, width, precision, length));
}


/**
 * percent_spec - prints a percentage sign
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: one printed character
 */
int percent_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length)
{
	int printed;

	NOT_USED(arg);
	NOT_USED(flags);
	NOT_USED(length);
	NOT_USED(precision);
	NOT_USED(width);
	NOT_USED(buff);

	printed = write(1, "%%", 1);

	return (printed);
}

/**
 * b_spec - prints unsigned numbers in binary format
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed character
 */
int b_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length)
{
	unsigned int num, mask;
	char z;
	int bit, leadZeros = 1, printed = 0;

	NOT_USED(buff);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(length);
	NOT_USED(precision);

	num = va_arg(arg, unsigned int);
	mask = 1 << 31;

	while (mask > 0)
	{
		bit = (mask & num) != 0;
		if (bit || leadZeros)
		{
			z = '0' + bit;
			write(1, &z, 1);
			printed++;
		}
	}
	return (printed);
}

/**
 * s_spec - prints a string
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed character
 */
int s_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length)
{
	int i, l = 0;
	char *s = va_arg(arg, char *);
	int padding;

	NOT_USED(buff);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(flags);
	NOT_USED(length);

	if (s == NULL)
	{
		s = "nil";
		if (precision >= 3)
			s = "   ";
	}
	while (s[l] != '\0')
		l++;
	if (precision < l && precision >= 0)
		l = precision;
	padding = width - l;

	if (width > l)
	{
		if (flags & FLAG_MINUS)
		{
			write(1, &s, l);
			for (i = padding; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = padding; i > 0 ; i--)
				write(1, " ", 1);
			write(1, &s[0], l);
			return (width);
		}
	}
	return (write(1, s, l));
}
