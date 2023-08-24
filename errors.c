#include "shell.h"

/**
 * _eputs - writes an input str to stderr
 * @str: The written str
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
 * _eputchar - Writes the c to stderr
 * @c: The printed char
 *
 * Return:  sets errno while -1 on error and 1 on success
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
 * _putfd - Writes c char to the given fd
 * @c: The char to be written
 * @fd: The destination where char is written to
 *
 * Return:  sets errno and return 1 on success and -1 otherwise
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
 * _putsfd - writes input str to the fd
 * @str: the written str
 * @fd: The fd written to
 *
 * Return: char number
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
