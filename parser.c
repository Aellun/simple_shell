#include "shell.h"

/**
 * is_cmd - Check if a file is an executable command.
 * @info: Pointer to the shell's info_t structure (unused).
 * @path: Path to the file to check.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(__attribute__((unused)) info_t *info, char *path)
{
	struct stat st;

	if (!path || stat(path, &st) != 0)
		return (0);

	return (S_ISREG(st.st_mode));
}

/**
 * dup_chars - Duplicate characters from a string within a specified range.
 * @pathstr: The string to duplicate characters from.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to the new buffer containing duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i, k = 0;

	for (i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			buf[k++] = pathstr[i];
		}
	}
	buf[k] = '\0';
	return (buf);
}

/**
 * find_path - Find the full path of a command in the PATH string.
 * @info: Pointer to the shell's info_t structure.
 * @pathstr: The PATH string containing directories.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, otherwise NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if (_strlen(cmd) > 2 && starts_with(cmd, "./") && is_cmd(info, cmd))
	{
		return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);

			if (!*path)
				_strcpy(path, cmd);
			else
				_strcat(path, "/");
			_strcat(path, cmd);

			if (is_cmd(info, path))
				return (path);

			if (!pathstr[i])
				break;

			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

