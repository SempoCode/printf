#include "main.h"

/**
 * write_char - Prints a string
 * @z: character to write
 * @buff: array to handle print
 * @flags:  Calculates active flags.
 * @width: get width
 * @precision: precision specifier
 * @length: length modifiers
 * Return: number of printed characters
 */
int write_char(char z, char buff[], int flags, int width,
	       int precision, int length)
{
	char pad = ' ';
	int i = 0, ch, ch1;

	NOT_USED(precision);
	NOT_USED(length);

	if (flags & FLAG_ZERO)
		pad = '0';
	buff[i++] = z;
	buff[i] = '\0';
	if (width > 1)
	{
		buff[LOCAL_BUFF - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buff[LOCAL_BUFF - i - 2] = pad;
		if (flags & FLAG_MINUS)
		{
			ch = write(1, &buff[0], 1);
			ch1 = write(1, &buff[LOCAL_BUFF - i - 1], width - 1);
			return (ch + ch1);
		}
		else
		{
			ch = write(1, &buff[0], 1);
			ch1 = write(1, &buff[LOCAL_BUFF - i - 1], width - 1);
			return (ch1 + ch);
		}
	}
	return (write(1, &buff[0], 1));
}

/**
 * write_num - Write a number using a bufffer
 * @k: index at which the number starts on the buffer.
 * @buff: Buffer
 * @flags: active flags
 * @width: width
 * @precision: Precision specifier
 * @n: number length to be printed
 * @pad: pading character
 * @c: the extra character
 * Return: Number of printed characters.
 */
int write_num(int k, char buff[], int flags, int width, int precision,
	int n, char pad, char c)
{
	int i, s_pad = 1;

	if (precision == 0 && k == LOCAL_BUFF - 2 && buff[k] == '0' && width == 0)
		return (0);
	if (precision == 0 && k == LOCAL_BUFF - 2 && buff[k] == '0')
		buff[k] = pad = ' ';
	if (precision > 0 && precision < n)
		pad = ' ';
	while (precision > n)
		buff[--k] = '0', n++;
	if (c != 0)
		n++;
	if (width > n)
	{
		for (i = 1; i < width - n + 1; i++)
			buff[i] = pad;
		buff[i] = '\0';
		if (flags & FLAG_MINUS && pad == ' ')
		{
			if (c)
				buff[--k] = c;
			return (write(1, &buff[k], n) + write(1, &buff[1], i - 1));
		}
		else if (!(flags & FLAG_MINUS) && pad == ' ')
		{
			if (c)
				buff[--k] = c;
			return (write(1, &buff[1], i - 1) + write(1, &buff[k], n));
		}
		else if (!(flags & FLAG_MINUS) && pad == '0')
		{
			if (c)
				buff[--s_pad] = c;
			return (write(1, &buff[s_pad], i - s_pad) +
				write(1, &buff[k], n - (1 - s_pad)));
		}
	}
	if (c)
		buff[--k] = c;
	return (write(1, &buff[k], n));
}


/**
 * write_number - Prints a number
 * @isNeg: boolean for number type
 * @k: integer
 * @buff: array to handle print
 * @flags:  Calculates active flags.
 * @width: get width
 * @precision: precision specifier
 * @length: length modifiers
 * Return: number of printed characters
 */
int write_number(int isNeg, int k, char buff[], int flags, int width,
	       int precision, int length)
{
	char pad = ' ', ch;
	int c = 0;
	int n = LOCAL_BUFF - k - 1;

	NOT_USED(length);

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		pad = '0';
	if (flags & FLAG_PLUS)
		ch = '+';
	else if (flags & FLAG_SPACE)
		ch = ' ';
	else if (isNeg)
		ch = '-';
	c = write_num(k, buff, flags, width, precision, n, pad, ch);
	return (c);
}


/**
 * writePointer - Write a memory address
 * @buff: Arrays of chars
 * @k: Index at which the number starts in the buffer
 * @n: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @pad: Char representing the padding
 * @c: Char representing extra char
 * @s_pad: Index at which padding should start
 * Return: Number of written chars.
 */
int writePointer(char buff[], int k, int n, int width, int flags,
		char pad, char c, int s_pad)
{
	int i;

	if (width > n)
	{
		for (i = 3; i < width - n + 3; i++)
			buff[i] = pad;
		buff[i] = '\0';
		if (flags & FLAG_MINUS && pad == ' ')
		{
			buff[--k] = 'x';
			buff[--k] = '0';
			if (c)
				buff[--k] = c;
			return (write(1, &buff[k], n) + write(1, &buff[3], i - 3));
		}
		else if (!(flags & FLAG_MINUS) && pad == ' ')
		{
			buff[--k] = 'x';
			buff[--k] = '0';
			if (c)
				buff[--k] = c;
			return (write(1, &buff[3], i - 3) +
					write(1, &buff[k], n));
		}
		else if (!(flags & FLAG_MINUS) && pad == '0')
		{
			if (c)
				buff[--s_pad] = c;
			buff[1] = '0';
			buff[2] = 'x';
			return (write(1, &buff[s_pad], i - s_pad) +
				write(1, &buff[n], n - (1 - s_pad) - 2));
		}
	}
	buff[--k] = 'x';
	buff[--k] = '0';
	if (c)
		buff[--k] = c;
	return (write(1, &buff[k], LOCAL_BUFF - k - 1));
}


/**
 * writeUnsignd - Writes an unsigned number
 * @isNeg: Number indicating if the num is negative
 * @k: Index at which the number starts in the buffer
 * @buff: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @length: length modifier
 * Return: Number of written characters
 */
int writeUnsignd(int isNeg, int k, char buff[], int flags, int width,
		int precision, int length)
{
	int n = LOCAL_BUFF - k - 1;
	int i = 0;
	char pad = ' ';

	NOT_USED(isNeg);
	NOT_USED(length);

	if (precision == 0 && k == LOCAL_BUFF - 2 && buff[k] == '0')
		return (0);
	if (precision > 0 && precision < n)
		pad = ' ';
	while (precision > n)
	{
		buff[--k] = '0';
		n++;
	}
	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		pad = '0';
	if (width > n)
	{
		for (i = 0; i < width - n; i++)
			buff[i] = pad;
		buff[i] = '\0';
		if (flags & FLAG_MINUS)
		{
			return (write(1, &buff[k], n) + write(1, &buff[0], i));
		}
		else
		{
			return (write(1, &buff[0], i) + write(1, &buff[k], n));
		}
	}

	return (write(1, &buff[k], n));
}
