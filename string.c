#include "shell.h"

/**
 * _strlen - print str len
 * @s: the str whose len is bieng evaluated
 * Return: int len of str
 */
int _strlen(char *s)
{
	int l = 0;

	if (!s)
		return (0);
	while (*s++)
		l++;
	return (l);
}
/**
 * _strcmp - performs dictionary checks of two strs
 * @s1: the first str to be checked
 * @s2: the second str to be checked
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
 * starts_with - if a string starts with a given substring
 * @haystack: str to search within
 * @needle: the substring to look for
 * Return: ptr to next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - join two strs
 * @dest: the dest to be joined to
 * @src: the source being joined to the other
 * Return: ptr to dest buf
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
