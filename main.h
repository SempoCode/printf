#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>

#define NOT_USED(c) (void)(c)

#define LOCAL_BUFF 1024

#define FLAG_PLUS (1 << 0)
#define FLAG_SPACE (1 << 1)
#define FLAG_HASH (1 << 2)
#define FLAG_ZERO (1 << 3)
#define FLAG_MINUS (1 << 4)

#define LENGTH_SHORT 1
#define LENGTH_LONG 2

int _printf(const char *format, ...);
int fprint(const char *format, int *index, va_list arg, char buff[], int flags,
		int width, int precision, int lenth);
void bufferPrint(char buffer[], int *index);

/**
 * struct fnOp - Structure of a character with associated function
 * @opt: The format.
 * @func: the function associated.
 */
struct fnOp
{
	char opt;
	int (*func)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fnOp op_t - new name
 */
typedef struct fnOp op_t;

int unsigned_x(va_list arg, char buff[], int flags, int width,
		int precision, int length);
int unsigned_X(va_list arg, char buff[], int flags, int width,
		int precision, int length);
int unsigned_o(va_list arg, char buff[], int flags, int width,
		int precision, int length);
int unsigned_n(va_list arg, char buff[], int flags, int width,
		int precision, int length);
int printHexa(va_list arg,char  mapArr[], char buff[], int flags, char spec,
		int width, int precision, int length);
int nonPrintable(va_list arg, char buff[], int flags, int width, int precision,
		int length);
int p_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length);
int rot13_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length);
int c_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length);
int int_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length);
int percent_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length);
int b_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length);
int s_spec(va_list arg, char buff[], int flags, int width, int precision,
		int length);
int write_char(char z, char buff[], int flags, int width,
		int precision, int length);
int write_num(int k, char buff[], int flags, int width, int precision,
		int n, char pad, char c);
int write_number(int isNeg, int k, char buff[], int flags, int width,
		int precision, int length);
int writePointer(char buffer[], int k, int n, int width, int flags,
		char pad, char c, int s_pad);
int writeUnsignd(int isNeg, int k, char buff[], int flags, int width,
		int precision, int length);
long int size_Convert(long int n, int length);
int is_digit(char z);
int hexa_code(char ascii, char buff[], int i);
int is_printable(char z);
long int sizeConvert(unsigned long int n, int length);
int is_alpha(char z);
int is_lower(char z);
int active_flag(const char *format, int *index);
int length_modifier(const char *format, int *index);
int reverse_string(va_list str, char buff[], int flags, int width,
		int precision, int length);
int field_width(const char *format, int *index, va_list arg);
int calc_precision(const char *format, int *index, va_list arr);

#endif
