#include "main.h"
/**
 * reverse_string - prints string in reverse
 * @str: variable list
 * @buff: an array
 * @flags: active flags
 * @width: formatted string widtah
 * @precision: precision for formatted string
 * @length: length modifier
 * Return: number of characters
 */
int reverse_string(va_list str, char buff[], int flags, int width,
int precision, int length)
{
	NOT_USED(buff);
	NOT_USED(flags);
	NOT_USED(length);
	NOT_USED(width);

	int count = 0, l = 0, i;
	char *s = va_arg(str, char *);

	if (s == NULL)
	{
		NOT_USED(precision);
		s = "nill";
	}

	while (s[l] != '\0')
		l++;
	for (i = l - 1; i >= 0; i--)
	{
		char z = s[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}


