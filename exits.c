#include "shell.h"

/**
 * _strncpy - Copies a string up to n characters.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int k;

	for (k = 0; src[k] != '\0' && k < n - 1; k++)
		dest[k] = src[k];

	/*Fill remaining characters in destination with null terminators*/
	while (k < n)
		dest[k++] = '\0';

	return (dest);
}

/**
 * _strncat - Concatenates two strings, up to n characters from src.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of characters to concatenate from src.
 *
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int k, j;

	for (k = 0; dest[k] != '\0'; k++)
		;/*Find the end of dest*/

	for (j = 0; src[j] != '\0' && j < n; j++)
		dest[k + j] = src[j];

	dest[k + j] = '\0';/*Null-terminate the concatenated string*/

	return (dest);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: ptr to memory where c is found in s, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);/*Return NULL if c is not found*/
}

