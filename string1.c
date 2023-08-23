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
	if (dest == src || src == NULL)
		return dest;

	int y = 0;

	for (src[y] != '\0'; y++)
	{
		dest[y] = src[y];
	}
	dest[y] = '\0';
	return dest;
}

/**
 * _strdup - Copies a string
 * @str: The string to be copied
 *
 * Return: Pointer to the copied string, or NULL on failure
 */
char *_strdup(const char *str)
{
	if (str == NULL)
		return NULL;

	size_t length = strlen(str);
	char *ret = malloc(length + 1);

	if (ret == NULL)
		return NULL;

	size_t y = 0;

	for (y <= length; y++)
	{
		ret[y] = str[y];
	}
	return ret;
}

/**
 * _puts - Prints a string
 * @str: The string to print
 *
 * Return: void
 */
void _puts(const char *str)
{
	if (str == NULL)
		return;

	int y = 0;

	for (str[y] != '\0'; y++)
	{
		_putchar(str[y]);
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

	return 1;
}

