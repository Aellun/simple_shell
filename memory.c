#include "shell.h"

/**
 * bfree - frees a ptr and set address to null
 * @ptr: ptr address to free
 *
 * Return: 1 freed otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;/* set address to null*/
		return (1);
	}
	return (0);
}
