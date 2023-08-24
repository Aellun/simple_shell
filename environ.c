#include "shell.h"

/**
 * _myenv - displays the current environment
 * @info: Struct having possible arg. Used to maintain
 *          constant function prototype.
 * Return: 0 on success
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - fetch value of the environ var
 * @info: Struct having potential arg Used to maintain
 * @name: name of the env var
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *y;

	while (node)
	{
		y = starts_with(node->str, name);
		if (y && *y)
			return (y);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - Initialize or modify a new environment var,
 * @info: struct having possible arg for const funct prototype
 *  Return: Always 0 on success
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _myunsetenv - terminate var for environ
 * @info: struct having possible arg for const funct prototype
 * Return: Always 0 on success
 */
int _myunsetenv(info_t *info)
{
	int m;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (m = 1; m <= info->argc; m++)
		_unsetenv(info, info->argv[m]);

	return (0);
}
/**
 * populate_env_list - populates env linked list
 * @info: struct having possible arg for const funct prototype
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
