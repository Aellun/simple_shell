#include "shell.h"
/**
 * list_len - determines length of linked list
 * @h: ptr to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * list_to_strings - prints array strof the list->str
 * @head: ptr to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t n = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !n)
		return (NULL);
	strs = malloc(sizeof(char *) * (n + 1));
	if (!strs)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < n; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[n] = str;
	}
	strs[n] = NULL;
	return (strs);
}


/**
 * print_list - writes all elements of a list_t linked list
 * @h: ptr to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * node_starts_with - display node str  with prefix at the begining
 * @node: ptr to list head
 * @prefix: str to be  match
 * @c: next char after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - fetch node index
 * @head: ptr to list head
 * @node: ptr to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}

