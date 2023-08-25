#include "shell.h"

/**
 * _eputs - displays an input str
 * @str: tthe written str
 * Return: Nothing
 */
void _eputs(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_eputchar(str[m]);
		m++;
	}
}
/**
 * _eputchar - writes the character c to stderr
 * @c: the written char
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * _putfd - displays the char c to the  given fd
 * @c: The character to b written
 * @fd: the dest where the char is written to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - displays an input str
 * @str: the str  printed
 * @fd: the dest to write to
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int m = 0;

	if (!str)
		return (0);
	while (*str)
	{
		m += _putfd(*str++, fd);
	}
	return (m);
}
