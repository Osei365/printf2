#include "main.h"
/**
 * write_char - writes chars
 * @ch: character to write
 * @buf: buffe
 * @precision: precision
 * @width: width
 * @flag: flag
 * @size: size
 * Return: printed characters
 */
int write_char(char ch, char buf[], int precision, int width,
		int flag, int size)
{
	int a = 0;
	char padding = ' ';

	(void)(precision);
	(void)(size);
	if (flag & 4)
		padding = '0';
	buf[a++] = ch;
	buf[a] = '\0';

	if (width > 1)
	{
		buf[BUFF_SIZE - 1] = '\0'; 
		for (a = 0; a < width - 1; a++)
		{
			buf[BUFF_SIZE - a - 2] = padding;
		}
		if (flag & 1)
		{
			return (write(1, &buf[0], 1) + write(1, &buf[BUFF_SIZE - a - 1], width - 1));
		}
		else
		{
			return (write(1, &buf[BUFF_SIZE - a - 1], width - 1) + write(1, &buf[0], 1));
		}
	}
	return (write(1, &buf[0], 1));
}

/**
 * write_int - write the int to stdout
 * @negative_bool: if the int is neg or not
 * @ind: index position
 * @buf: buffer
 * @precision: preciion
 * @width: width
 * @size: size
 * @Return: int
 */
int write_int(int negative_bool, int ind, char buf[], int precision, int width,
		int size, int flag)
{
	int l = BUFF_SIZE - ind - 1;
	char padding = ' ', ch = 0;

	(void)(size);
	if ((flag & 4) && !(flag & 1))
		padding = '0';
	if (negative_bool)
		ch = '-';
	else if (flag & 2)
		ch = '+';
	else if (flag & 16)
		ch = ' ';

	return (write_integer(ind, buf, precision, width, flag, l, ch, padding));
}

/**
 * write_integer - writes integer
 * @ind: index position after 5
 * @buf: buffer
 * @precision: precision of the sepc 
 * @width: width of the specifier
 * @flag: flag
 * @l: legnth of the spec
 * @ch: extra characters to join to output
 * @padding: padding to join
 * Return: int
 */
int write_integer(int ind, char buf[], int precision, int width, int flag, int l,
		char ch, char padding)
{
	int a, padding_start = 1;

	if (precision == 0 && width == 0 && ind == BUFF_SIZE - 2 && buf[ind] == '0')
		return (0);
	if (precision == 0 && ind == BUFF_SIZE - 2 && buf[ind] == '0')
	{
		buf[ind] = ' ';
		padding = ' ';
	}
	if (precision > 0 && precision < l)
		padding = ' ';
	for (; precision > l; l++)
		buf[--ind] = '0';
	if (ch != 0)
		l++;
	if (width > l)
	{
		for (a = 1; a < width - l + 1; a++)
			buf[a] = padding;
		buf[a] = '\0';
		if (flag & 1 && padding == ' ')
		{
			if (ch)
				buf[--ind] = ch;
			return (write(1, &buf[ind], l) + write(1, &buf[1], a - 1));
		}
		else if (!(flag & 1) && padding == ' ')
		{
			if (ch)
				buf[--ind] = ch;
			return (write(1, &buf[1], a - 1) + write(1, &buf[ind], l));
		}
		else if (!(flag & 1) && padding == '0')
		{
			if (ch)
				buf[--padding_start] = ch;
			return (write(1, &buf[padding_start], a - padding_start) +
				write(1, &buf[ind], l - (1 - padding_start)));
		}
	}
	if (ch)
		buf[--ind] = ch;
	return (write(1, &buf[ind], l));
}

/**
 * write_unsigned - write unsigned int to stdout
 * @negative_bool: negative int or not
 * @ind: index position in buffer
 * @buf: buffer
 * @flag: flag
 * @width: width
 * @precision: precision
 * @size: size
 * Return: int
 */
int write_unsigned(int negative_bool, int ind, char buf[], int flag, 
		int width, int precision, int size)
{
	int l = BUFF_SIZE - ind - 1, a = 0;
	char padding = ' ';

	(void)(negative_bool);
	(void)(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buf[ind] == '0')
		return (0);

	if (precision > 0 && precision < l)
		padding = ' ';

	for (; precision > l; l++)
	{
		buf[--ind] = '0';
	}

	if ((flag & 4) && !(flag & 1))
		padding = '0';

	if (width > l)
	{
		for (a = 0; a < width - l; a++)
			buf[a] = padding;

		buf[a] = '\0';

		if (flag & 1)
		{
			return (write(1, &buf[ind], l) + write(1, &buf[0], a));
		}
		else
		{
			return (write(1, &buf[0], a) + write(1, &buf[ind], l));
		}
	}

	return (write(1, &buf[ind], l));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
