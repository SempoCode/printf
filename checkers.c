#include "main.h"

/**
 * size_Convert - casts a number to the specified size for integer
 * @n: number to be casted.
 * @length: number indicating the length to be casted.
 * Return: the casted value of n
 */
long int size_Convert(long int n, int length)
{
	if (length == LENGTH_LONG)
		return (n);
	else if (length == LENGTH_SHORT)
		return ((short)n);
	return ((int)n);
}

/**
 * is_digit - checks if a character is a digit
 * @z: character to be checked
 * Return: 1 if z is a digit, 0 otherwise
 */
int is_digit(char z)
{
	if (z >= '0' && z <= '9')
		return (1);
	return (0);
}

/**
 * hexa_code - appends ascci code in hexadecimal
 * @buff: array of chararcters
 * @i: index at which to start appending.
 * @ascii: ASSCI CODE
 * Return: Always 3
 */
int hexa_code(char ascii, char buff[], int i)
{
	char mapArr[] = "0123456789ABCDEF";

	if (ascii < 0)
		ascii *= -1;
	buff[i++] = '\\';
	buff[i++] = 'x';
	buff[i++] = mapArr[ascii / 16];
	buff[i] = mapArr[ascii % 16];
	return (3);
}

/**
 * is_printable - checks if a character is printable
 * @z: character to be checked
 * Return: 1 if z is printable, 0 otherwise
 */
int is_printable(char z)
{
	if (z >= 32 && z < 127)
		return (1);
	return (0);
}

/**
 * sizeConvert - Casts a number to the specified size in unsigned
 * @n: number to be casted
 * @length: number indicating the length to be casted
 * Return: casted value of n
 */
long int sizeConvert(unsigned long int n, int length)
{
	if (length == LENGTH_LONG)
		return (n);
	else if (length == LENGTH_SHORT)
		return ((unsigned short)n);
	return ((unsigned int)n);
}
