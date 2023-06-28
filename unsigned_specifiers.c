#include "main.h"

/**
 * unsigned_n - prints unsigned number
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed characters
 */
int unsigned_n(va_list arg, char buff[], int flags, int width,
		int precision, int length)
{
	unsigned long int n;
	int counter, ch;

	n = va_arg(arg, unsigned long int);
	n = sizeConvert(n, length);
	counter = LOCAL_BUFF - 2;

	if (n == 0)
		buff[counter--] = '0';
	buff[LOCAL_BUFF - 1] = '\0';
	while (n > 0)
	{
		buff[counter--] = (n % 10) + '0';
		n /= 10;
	}
	counter++;
	ch = writeUnsignd(0, counter, buff, flags, width, precision, length);
	return (ch);
}


/**
 * unsigned_o - prints unsigned number in octal
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed characters
 */
int unsigned_o(va_list arg, char buff[], int flags, int width,
		int precision, int length)
{
	unsigned long int n = va_arg(arg, unsigned long int);
	int counter = LOCAL_BUFF - 2, ch;
	unsigned long int num = n;

	NOT_USED(precision);
	NOT_USED(width);

	n = sizeConvert(n, length);
	if (n == 0)
		buff[counter--] = '0';
	buff[LOCAL_BUFF - 1] = '\0';
	while (n > 0)
	{
		buff[counter--] = (n % 10) + '0';
		n /= 10;
	}
	if (flags & FLAG_HASH && num != 0)
		buff[counter--] = '0';
	counter++;
	ch = writeUnsignd(0, counter, buff, flags, width, precision, length);
	return (ch);
}


/**
 * printHexa - prints unsigned number in hexadecimal
 * @arg: list of arguments (of type va_list)
 * @mapArr: array of of hexdecimal characters
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @spec: character specifier
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed characters
 */
int printHexa(va_list arg, char mapArr[], char buff[], int flags, char spec,
		int width, int precision, int length)
{
	unsigned long int n = va_arg(arg, unsigned long int);
	unsigned long int num = n;
	int counter = LOCAL_BUFF - 2, ch;

	NOT_USED(width);

	n = sizeConvert(n, length);
	if (n == 0)
		buff[counter--] = '0';
	buff[LOCAL_BUFF - 1] = '\0';
	while (n > 0)
	{
		buff[counter--] = mapArr[n % 16];
		n /= 16;
	}
	if (flags & FLAG_HASH && num != 0)
	{
		buff[counter--] = spec;
		buff[counter--] = '0';
	}
	counter++;
	ch = writeUnsignd(0, counter, buff, flags, width, precision, length);
	return (ch);
}


/**
 * unsigned_X - prints unsigned number in upper hexadecimal
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed characters
 */
int unsigned_X(va_list arg, char buff[], int flags, int width,
		int precision, int length)
{
	int ch;

	ch = printHexa(arg, "0123456789abcdef", buff, flags, 'X', width,
			precision, length);
	return (ch);
}


/**
 * unsigned_x - prints unsigned number in lower hexadecimal
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed characters
 */
int unsigned_x(va_list arg, char buff[], int flags, int width,
		int precision, int length)
{
	int ch;

	ch = printHexa(arg, "0123456789abcdef", buff, flags, 'x', width,
			precision, length);
	return (ch);
}
