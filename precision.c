#include "main.h"
/**
 * calc_precision - calculates the value for printing
 * @format: pointer to formatted string
 * @index: pointer to the current index in the format string
 * @arr: variable list containing arguments
 * Return: precision value
 */
int calc_precision(const char *format, int *index, va_list arr)
{
	int i = 1 + *index, prec_value = -1;

	if (format[i] == '.')
	{
		prec_value = 0;
		i++;
		while (is_digit(format[i]))
		{
			prec_value *= 10;
			prec_value += format[i] - '0';
			i++;
		}
		if (format[i] == '*')
		{
			i++;
			prec_value = va_arg(arr, int);
		}
	}
	*index = i - 1;
	return (prec_value);
}
