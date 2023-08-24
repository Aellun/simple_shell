#include "shell.h"

/**
 **_strncpy - cduplicate the str
 *@src: where the str is dup from
 *@dest: the dest to dup to
 *@n: number str to dup
 *Return: the joined str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int m, k;
	char *s = dest;

	m = 0;
	while (src[m] != '\0' && m < n - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < n)
	{
		k = m;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}
/**
 **_strncat - combine two str
 *@dest: the str to join to
 *@src: the one being joined to another
 *@n: the amount of bytes to be maximally used
 *Return: the combined str
 */
char *_strncat(char *dest, char *src, int n)
{
	int m, k;
	char *s = dest;

	m = 0;
	k = 0;
	while (dest[m] != '\0')
		m++;
	while (src[k] != '\0' && k < n)
	{
		dest[m] = src[k];
		m++;
		k++;
	}
	if (k < n)
		dest[m] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a str
 *@s: the str to be parsed
 *@c: the char to look for
 *Return: (s) a ptr to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

