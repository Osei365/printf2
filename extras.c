#include "main.h"

/**
 * is_printable - checks if char is printable
 * @ch: Char
 *
 * Return: 1 if c is printable, 0 else
 */
int is_printable(char ch)
{
	if (ch >= 32 && ch < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buf: Array of chars.
 * @ind: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 *
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buf[], int ind)
{
	char map[] = "0123456789ABCDEF";
	if (ascii_code < 0)
		ascii_code *= -1;

	buf[ind++] = '\\';
	buf[ind++] = 'x';

	buf[ind++] = map[ascii_code / 16];
	buf[ind] = map[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @ch: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == 2)
		return (num);
	else if (size == 1)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == 2)
		return (num);
	else if (size == 1)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
