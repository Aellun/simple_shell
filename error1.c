#include "shell.h"

/**
 * _erratoi - turns str to an int
 * @s: The converted str
 *
 * Return: -1 on error.
 */
int _erratoi(char *s)
{
	int n = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;/*Skip leading plus sign*/
	for (n = 0; s[n] != '\0'; n++)
	{
		if (s[n] >= '0' && s[n] <= '9')
		{
			result *= 10;
			result += (s[n] - '0');
			if (result > INT_MAX)
				return (-1);/*Overflow condition*/
		}
		else
			return (-1);/*Non-numeric character encountered*/
	}
	return (result);
}

/**
 * print_error -writes an err msg to stderr.
 * @info: The parameter and return info struct.
 * @estr: Str containing specified err
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);/*Print file name*/
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);/*Print line number*/
	_eputs(": ");
	_eputs(info->argv[0]);/*Print command name*/
	_eputs(": ");
	_eputs(estr);/*Print error message*/
}

/**
 * print_d - writes an in number to a given fd
 * @input: The number to be written
 * @fd: The destination fd
 *
 * Return: charcters written in numbers
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
	int n, count = 0;
	unsigned int _abs_, current;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

	/*Iterate through each decimal place and print digits*/
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_abs_ / n)
		{
			__putchar('0' + current / n);
			count++;
		}
		current %= n;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - turns num to str rep in a given base.
 * @num: The num to turn
 * @base: The base for conversion like decimal, hexadecimal
 * @flags: Arg flag
 *
 * Return: The str conveted
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	/* Set the array of characters for the given base*/
	array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];/*Start from the end of the buffer*/
	*ptr = '\0';/*Null-terminate the string*/

	/* Convert the number to the specified base*/
	do {
		*--ptr = array[n % base];/*Insert the remainder at the beginning*/
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;/*Add the sign if negative*/
	return (ptr);/*Return the converted string*/
}

/**
 * remove_comments -exchanges the 1st occurance of '#' with '\0'.
 * @buf: The address of the str to modify.
 */
void remove_comments(char *buf)
{
	int n;

	/* Iterate through the string to find '#' preceded by a space*/
	for (n = 0; buf[n] != '\0'; n++)
		if (buf[n] == '#' && (!n || buf[n - 1] == ' '))
		{
			buf[n] = '\0';/*Replace '#' with null terminator*/
			break;
		}
}

