#include "shell.h"

/**
 * safe_free - safely frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int safe_free(void **ptr)
{
	/* Check if  not NULL and if is not pointing to NULL */
	if (ptr && *ptr)
	{
		/* Free the pointer */
		free(*ptr);

		/* NULL the pointer */
		*ptr = NULL;

		return (1);
	}

	return (0);
}

