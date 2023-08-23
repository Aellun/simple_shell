#include "shell.h"

/**
 * _strcpy - Copies a string
 * @dest: Destination where the string is copied to
 * @src: Source string to be copied
 *
 * Return: Pointer to destination string
 */
char *_strcpy(char *dest, const char *src)
{
	int y = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[y] != '\0')
	{
		dest[y] = src[y];
		y++;
	}
	dest[y] = '\0';
	return (dest);
}

/**
 * _strdup - Copies a string
 * @str: The string to be copied
 *
 * Return: Pointer to the copied string, or NULL on failure
 */
char *_strdup(const char *str)
{
	size_t y = 0;
	size_t length = strlen(str);
	char *ret = malloc(length + 1);

	if (str == NULL)
		return (NULL);

	if (ret == NULL)
		return (NULL);

	while (y <= length)
	{
		ret[y] = str[y];
		y++;
	}
	return (ret);
}

/**
 * _puts - Prints a string
 * @str: The string to print
 *
 * Return: void
 */
void _puts(const char *str)
{
	int y = 0;

	if (str == NULL)
		return;

	while (str[y] != '\0')
	{
		_putchar(str[y]);
		y++;
	}
}

/**
 * _putchar - Writes a character to stdout
 * @c: The character to write
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

