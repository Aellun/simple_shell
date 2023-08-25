#include "shell.h"

/**
 * is_cmd - finds if its an executable command
 * @info: the info struct
 * @path: path to the file specified
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_chars - copies char
 * @pathstr: PATH str
 * @start: the start index
 * @stop: the stop index
 *
 * Return: ptr to new buf
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int b = 0, p = 0;

	for (p = 0, b = start; b < stop; b++)
		if (pathstr[b] != ':')
			buf[p++] = pathstr[b];
	buf[p] = 0;
	return (buf);
}

/**
 * find_path - determine cmd in PATH str
 * @info: the info struct
 * @pathstr: the PATH str to use
 * @cmd: the cmd to find
 *
 * Return: full path if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int b = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[b] || pathstr[b] == ':')
		{
			path = dup_chars(pathstr, curr_pos, b);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[b])
				break;
			curr_pos = b;
		}
		b++;
	}
	return (NULL);
}

