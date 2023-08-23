#include "shell.h"

/**
 * _strcpy - reprints a str
 * @dest: where the str is copied to
 * @src: where the str is reprinted from
 *
 * Return: ptr to dest
 */
char *_strcpy(char *dest, char *src)
{
	if (dest == src || src == NULL)
		return (dest);

	int y;

	for (y = 0; src[y] != '\0'; y++)
	{
		dest[y] = src[y];
	}
	dest[y] = '\0';
	return (dest);
}

/**
 * _strdup - copies the str
 * @str: the str to be copied
 *
 * Return: ptr to the copied str
 */
char *_strdup(const char *str)
{
	if (str == NULL)
		return (NULL);

	size_t length = strlen(str);
	char *ret = malloc(length + 1);

	if (ret == NULL)
		return (NULL);

	size_t y;

	for (y = 0; y <= length; y++)
	{
		ret[y] = str[y];
	}
	return (ret);
}

/**
 * _puts - prints the input str
 * @str: the str to print
 *
 * Return: void
 */
void _puts(const char *str)
{
	if (str == NULL)
		return;

	int y;

	for (y = 0; str[y] != '\0'; y++)
	{
		_putchar(str[y]);
	}
}

/**
 * _putchar - signs the char c to stdout
 * @c: The char to sign
 *
 * Return: 1 on success, -1 on error
 */
int _putchar(char c)
{
	static int y;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || y >= WRITE_BUF_SIZE)
	{
		write(1, buf, y);
		y = 0;
	}

	if (c != BUF_FLUSH)
		buf[y++] = c;

	return (1);
}
