#include "shell.h"

/**
 * _strlen - returns the len of a str
 * @s: the str whose len to scan
 *
 * Return: integer len of str
 */
int _strlen(char *s)
{
	int z = 0;

	if (!s)
		return (0);

	while (*s++)
		z++;
	return (z);
}

/**
 * _strcmp - performs vocabulary comparison of 2 str
 * @s1: the 1 str
 * @s2: the 2nd str
 *
 * Return: -ve if s1 < s2, +ve if s1 > s2, 0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: stri to scan
 * @needle: the substr to check
 *
 * Return: ptr of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - join 2 str
 * @dest: where the str is joined to
 * @src: the source of the str to join
 *
 * Return: ptr to desti buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

