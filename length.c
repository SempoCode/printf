#include "main.h"
/**
 * length_modifier - calculates the argument length
 * @format: pointer to the format string
 * @index: pointer to the index of argument list
 * Return: length calculated
 */
int length_modifier(const char *format, int *index)
{
	int length = 0;

	switch (format[*index + 1])
	{
		case 'l':
			length = LENGTH_LONG;
			break;
		case 'h':
			length = LENGTH_SHORT;
			break;
		default:
			break;
	}
	return (length);
}
