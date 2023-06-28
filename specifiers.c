#include "main.h"


/**
 * is_alpha - checks if character is an alphabet
 * @z: the character
 * Return: 1 if it's character, otherwise 0
 */
int is_alpha(char z)
{
	return ((z >= 'a' && z <= 'z') || (z >= 'A' && z <= 'Z'));
}

/**
 * is_lower - checks if character is lower case alphabet
 * @z: the character
 * Return: 1 if it's character, otherwise 0
 */
int is_lower(char z)
{
	return ((z >= 'a' && z <= 'z'));
}


/**
 * rot13_spec - prints the rot13'ed string
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed characters
 */
int rot13_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length)
{
	char *s = va_arg(arg, char *);
	int printed = 0;
	char base;

	NOT_USED(buff);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(length);

	if (s == NULL)
		s = "nil";
	while (*s)
	{
		char z = *s;

		if (is_alpha(z))
		{
			base = is_lower(z) ? 'a' : 'A';
			z = (z - base + 13) % 26 + base;
		}
		write(1, &z, 1);
		printed += 1;
		s++;
	}
	return (printed);
}

/**
 * p_spec - prints the value of a pointer
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed characters
 */
int p_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length)
{
	int n = 2, printed, i = LOCAL_BUFF - 2, s_pad = 1;
	char pad = ' ', c = 0, mapArr[] = "0123456789abcdef";
	void *s = va_arg(arg, void *);
	unsigned long int num;

	NOT_USED(length);
	NOT_USED(width);

	if (s == NULL)
		return (write(1, "nil", 3));
	buff[LOCAL_BUFF - 1] = '\0';
	NOT_USED(precision);
	
	num = (unsigned long)s;

	while (num > 0)
	{
		buff[i--] = mapArr[num % 16];
		num /= 16;
		n++;
	}
	if (flags & FLAG_PLUS)
	{
		c = '+';
       		n++;
	}
	else if (flags & FLAG_SPACE)
	{
		c = ' ';
		n++;
	}
	if (!(flags & FLAG_MINUS) && (flags & FLAG_ZERO))
		pad = '0';
	i++;
	printed = writePointer(buff, i, n, width, flags, pad, c, s_pad);
	return (printed);
}


/**
 * nonPrintable - prints the ASCII codes of
 * non printable characters in hexadecimal
 * @arg: list of arguments (of type va_list)
 * @buff: an array for printing operation
 * @flags: calculats active flags
 * @width: width of the printed output
 * @precision: precision of the printed output
 * @length: length modifier
 * Return: number of printed characters
 */
int nonPrintable(va_list arg, char buff[], int flags, int width, int precision,
		int length)
{
	int base, ind = 0, ch;
	char *s = va_arg(arg, char *);

	NOT_USED(width);
	NOT_USED(length);
	NOT_USED(flags);
	NOT_USED(precision);

	if (s == NULL)
		return (write(1, "nil", 3));
	while (s[ind] != '\0')
	{
		if (is_printable(s[ind]))
			buff[base + ind] = s[ind];
		else
			base += hexa_code(s[ind], buff, ind + base);
		ind++;
	}
	buff[base + ind] = '\0';
	ch = write(1, buff, base + ind);

	return (ch);
}
