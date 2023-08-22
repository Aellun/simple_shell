#include "shell.h"

/**
 * get_user_input - gets user input
 *
 * Return: a pointer to the user input
 */
char *get_user_input(void)
{
	static char line[MAX_INPUT_SIZE]; /* Static buffer*/
	size_t len = 0;

	if (getline(&line, &len, stdin) == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	return (line);
}

/**
 * fork_cmd - forks a child process and executes a command
 * @info: the info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	if (child_pid == 0)
	{
		if (execvp(info->argv[0], info->argv) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	} else
	{
		int status;

		if (waitpid(child_pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			info->status = WEXITSTATUS(status);
		}
	}
}

