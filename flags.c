#include "main.h"
/**
 * active_flag - calculates the active flags in the strng
 * @format: pointer to the formatted string
 * @index: pointer to the index of the argument list
 * Return: active flags calculate
 */
int active_flag(const char *format, int *index)
{
	bool loop = true;
	int flags = 0;

	while (loop)
	{
		(*index)++;
		switch (format[*index])
		{
			case '+':
				flags |= FLAG_PLUS;
				break;
			case ' ':
				flags |= FLAG_SPACE;
				break;
			case '#':
				flags |= FLAG_HASH;
				break;
			case '0':
				flags |= FLAG_ZERO;
				break;
			case '-':
				flags |= FLAG_MINUS;
				break;
			default:
				loop = false;
				break;
		}
	}
	(*index)--;
	return (flags);
}
