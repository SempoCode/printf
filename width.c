#include "main.h"
/**
 * field_width - calculates the width of the printed value
 * @format: pointer to the formatted string
 * @index: pointer to the index of argument list
 * @arg: variable list
 * Return: width
 */
int field_width(const char *format, int *index, va_list arg)
{
	int width = 0, i = *index + 1;

	while (is_digit(format[i]))
	{
		width *= 10;
		width += (format[i] - '0');
		i++;
	}
	if (format[i] == *index)
	{
		i++;
		width = va_arg(arg, int);
	}
	*index = i - 1;
	return (width);
}

