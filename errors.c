#include "shell.h"

/**
 * _eputs - Prints an input string to standard error (stderr).
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int k = 0;

	if (!str)
		return;

	while (str[k] != '\0') /*Iterate through the string characters*/
	{
		_eputchar(str[k]); /*Print each character to stderr*/
		k++;
	}
}

/**
 * _eputchar - Writes the character c to standard error (stderr).
 * @c: The character to print.
 *
 * Return: On success, returns 1. On error, returns -1 and sets errno.
 */
int _eputchar(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buf, k); /*Write buffered characters to stderr*/
		k = 0;
	}

	if (c != BUF_FLUSH)
		buf[k++] = c; /*Buffer the character*/

	return (1);
}

/**
 * _putfd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1. On error, returns -1 and sets errno.
 */
int _putfd(char c, int fd)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k); /*Write buffered characters to the specified fd*/
		k = 0;
	}

	/*Add character to the buffer if not BUF_FLUSH*/
	if (c != BUF_FLUSH)
		buf[k++] = c;

	return (1);
}

/**
 * _putsfd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _putsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);


	/*Iterate over str & write each char specified fd*/
	while (*str)
	{
		k += _putfd(*str++, fd);
	}

	return (k);
}
