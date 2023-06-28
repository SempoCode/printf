#include "main.h"

int fprint(const char *format, int *index, va_list arg, char buff[], int flags,
		int width, int precision, int lenth);

/**
 * bufferPrint - prints the buffer content
 * @buffer: an arrya of characters to print
 * @index: pointer to index in the array
 * Return: nothing
 */
void bufferPrint(char buffer[], int *index)
{
	if (*index > 0)
	{
		write(1, &buffer[0], *index);
	}
	*index = 0;
}

/**
 * _printf - produces output according to a format like printf
 * @format: pointer to character string with directives
 * @...: variable parameters to the function
 * Return: the number of characters printed (excluding the
 * null byte used to end output to strings)
 */
int _printf(const char *format, ...)
{
	int length, flags, precision, width, i, index = 0, count = 0, ch = 0;
	char buff[LOCAL_BUFF];
	va_list arg;

	if (format == NULL)
		return (-1);
	va_start(arg, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buff[index++] = format[i];
			if (index == LOCAL_BUFF)
			{
				bufferPrint(buff, &index);
			}
			ch += 1;
		}
		else
		{
			bufferPrint(buff, &index);
			precision = calc_precision(format, &index, arg);
			flags = active_flag(format, &index);
			width = field_width(format, &index, arg);
			length = length_modifier(format, &index);
			++i;
			count = fprint(format, &i, arg, buff, flags, width,
					precision, length);
			if (count == -1)
			{
				va_end(arg);
				return (-1);
			}
			ch = ch + count;
		}
	}
	bufferPrint(buff, &index);
	va_end(arg);
	return (ch);
}


int fprint(const char *format, int *index, va_list arg, char buff[], int flags,
		int width, int precision, int length)
{
	int  i = 0, n = 0;
	op_t ft_op[] = {
		{'c', c_spec}, {'s', s_spec}, {'b', b_spec},
		{'%', percent_spec}, {'d', int_spec}, {'i', int_spec},
		{'r', reverse_string}, {'u', unsigned_n}, {'o', unsigned_o},
		{'x', unsigned_x}, {'X', unsigned_X}, {'p', p_spec},
		{'S', nonPrintable}, {'R', rot13_spec}, {'\0', NULL}
	};

	while (ft_op[i].opt != '\0')
	{
		if (format[*index] == ft_op[i].opt)
			return ((ft_op[i].func(arg, buff, flags, width,
							precision, length)));
		i++;
	}
	if (format[*index] == '\0')
	{
		return (-1);
	}
	n = n + write(1, "%%", 1);

	if (format[*index - 1] == ' ')
		n += write(1, " ", 1);
	else if (width)
	{
		(*index)--;
		while (format[*index] != ' ' && format[*index] != '%')
			(*index)--;
		if (format[*index] == ' ')
			(*index)--;
		return (1);
	}
	n += write(1, &format[*index], 1);
	return (n);
}
