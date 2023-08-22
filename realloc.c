#include "shell.h"

/**
 * mem_fill - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 *
 * Return: (s) a pointer to the memory area s
 */
void *mem_fill(void *s, char b, unsigned int n)
{
    /* Iterate over the memory area and fill each byte with the constant byte */
    unsigned int i;

    for (i = 0; i < n; i++)
    {
        *((char *)s + i) = b;
    }

    /* Return the pointer to the memory area */
    return s;
}

/**
 * free_strings - frees a string of strings
 * @strings: string of strings
 */
void free_strings(char **strings)
{
    /* Iterate over the strings and free each one */
    char **s = strings;

    while (*s)
    {
        safe_free((void **)s);
        s++;
    }

    /* Free the pointer to the array of strings */
    safe_free((void **)strings);
}

/**
 * realloc_mem - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the new block or NULL on failure
 */
void *realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *new_ptr;
    /* Check if the new size is zero */
    if (new_size == 0)
    {
        /* Free the old block and return NULL */
        safe_free(&ptr);
        return NULL;
    }

    /* Allocate a new block of memory */
    void *new_ptr = malloc(new_size);

    /* Check if the allocation failed */
    if (new_ptr == NULL)
    {
        /* Free the old block and return NULL */
        safe_free(&ptr);
        return NULL;
    }

    /* Copy the data from the old block to the new block */
    memcpy(new_ptr, ptr, old_size);

    /* Free the old block */
    safe_free(&ptr);

    /* Return the new block */
    return new_ptr;
}
