#include "shell.h"

/**
 * _erratoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: Converted number if valid, -1 on error.
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
 * print_error - Prints an error message to stderr.
 * @info: The parameter and return info struct.
 * @estr: String containing specified error type.
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
 * print_d - Prints a decimal (integer) number to a specified file descriptor.
 * @input: The input number to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
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
 * convert_number - Converts a number to a string rep in a given base.
 * @num: The number to be converted.
 * @base: The base for conversion (e.g., decimal, hexadecimal).
 * @flags: Argument flags.
 *
 * Return: The string representation of the converted number.
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
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
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

