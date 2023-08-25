#include "shell.h"

/**
 * is_chain - determine if current char in buffer is a chain delimeter
 * @info: ptr to the to struct
 * @buf: ptr to array buf
 * @p: ptr to size variable -t
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t d = *p;
	if (buf[d] == '|' && buf[d + 1] == '|')
	{
		buf[d] = 0;
		d++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[d] == '&' && buf[d + 1] == '&')
	{
		buf[d] = 0;
		d++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[d] == ';') /*end of this command */
	{
		buf[d] = 0; /*eplace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = d;
	return (1);
}
/**
 * check_chain - determine if should chaining based on the status last
 * @info: the ptr struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t d = *p;
	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			d = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			d = len;
		}
	}
	*p = d;
}

/**
 * replace_alias - put in plsce an aliases in the tokenized str
 * @info: the ptr struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int l;
	list_t *node;
	char *p;
	for (l = 0; l < 10; l++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
	/**
	 * replace_vars - replaces vars in the tokenized str
	 * @info: the ptr struct
	 * Return: 1 if replaced, 0 otherwise
	 */
	int replace_vars(info_t *info)
	{
		int l = 0;
		list_t *node;

		for (l = 0; info->argv[l]; l++)
		{
			if (info->argv[l][0] != '$' || !info->argv[l][1])
				continue;
			if (!_strcmp(info->argv[l], "$?"))
			{
				replace_string(&(info->argv[l]),
						_strdup(convert_number(info->status, 10, 0)));
				continue;
			}
			if (!_strcmp(info->argv[l], "$$"))
			{
				replace_string(&(info->argv[l]),
						_strdup(convert_number(getpid(), 10, 0)));
				continue;
			}
			node = node_starts_with(info->env, &info->argv[i][1], '=');
			if (node)
			{
				replace_string(&(info->argv[l]),
						_strdup(_strchr(node->str, '=') + 1));
				continue;
			}
			replace_string(&info->argv[i], _strdup(""));
		}
		return (0);
	}
	/**
	 * replace_string - replaces str
	 * @old: address of old string
	 * @new: new string
	 * Return: 1 if replaced, 0 otherwise
	 */
	int replace_string(char **old, char *new)
	{
		free(*old);
		*old = new;
		return (1);
	}

