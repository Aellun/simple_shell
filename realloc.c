#include "shell.h"

/**
 * _memset - fills memory with a byte that is const
 * @s: the ptr to the memory addr
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a ptr to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		s[m] = b;
	return (s);
}
/**
 * ffree - frees str of str
 * @pp: the str of strs
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
/**
 * _realloc - reallocates memory block
 * @ptr: ptr to previously alloacated block
 * @old_size:  previous block byte size
 * @new_size: new block byte size
 *
 * Return: ptr to allocated block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
