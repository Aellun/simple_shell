#include "shell.h"

/**
 * clear_info - Initializes info_t struct fields
 * @info: Pointer to the info_t struct to be initialized
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes info_t struct fields based on input arguments
 * @info: Pointer to the info_t struct to be initialized
 * @av: Argument vector
 */
void set_info(info_t *info, char **av)
{
	int i;

	info->fname = av[0];

	if (!info->arg)
		return;

	info->argv = strtow(info->arg, " \t");
	if (!info->argv)
	{
		info->argv = malloc(sizeof(char *) * 2);
		if (info->argv)
		{
			info->argv[0] = _strdup(info->arg);
			info->argv[1] = NULL;
		}
	}

	for (i = 0; info->argv && info->argv[i]; i++)
		;
	info->argc = i;

	replace_alias(info);
	replace_vars(info);
}

/**
 * free_info - Frees memory associated with info_t struct fields
 * @info: Pointer to the info_t struct whose memory needs to be freed
 * @all: True if all fields need to be freed, otherwise only specific fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (!all)
		return;

	if (!info->cmd_buf)
		free(info->arg);

	free_list(&(info->env));
	free_list(&(info->history));
	free_list(&(info->alias));
	ffree(info->environ);
	info->environ = NULL;
	free((void **)info->cmd_buf);

	if (info->readfd > 2)
		close(info->readfd);
	_putchar(BUF_FLUSH);
}

