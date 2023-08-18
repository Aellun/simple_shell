#include "shell.h"

/**
 * _myexit - Exit the shell with a specified exit status.
 * @info: Pointer to the shell's info_t structure.
 *
 * Return: Always returns -2 to indicate shell termination.
 */
int _myexit(info_t *info)
{
	int exit_status;

	if (info->argv[1]) /* If an exit status argument is provided */
	{
		exit_status = _erratoi(info->argv[1]);

		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		info->err_num = exit_status;
		return (-2); /* Return -2 to signal shell termination */
	}

	info->err_num = -1;
	return (-2); /* Return -2 to signal shell termination */
}

/**
 * _mycd - Change the current working directory of the shell.
 * @info: Pointer to the shell's info_t structure.
 *
 * Return: Always returns 0.
 */
int _mycd(info_t *info)
{
	char *cwd, *target_dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);

	if (!cwd)
		_puts("TODO: >>getcwd failure emsg here<<\n"); /* TODO: Add error handling for getcwd failure */

	if (!info->argv[1]) /* If no target directory is provided */
	{
		target_dir = _getenv(info, "HOME=");

		if (!target_dir)
			chdir_ret = chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/"); /* Change to HOME or PWD if available */
		else
			chdir_ret = chdir(target_dir); /* Change to the target directory */
	}
	else if (_strcmp(info->argv[1], "-") == 0) /* If target directory is "-" */
	{
		if (!_getenv(info, "OLDPWD=")) /* If OLDPWD is not set */
		{
			_puts(cwd);
			_putchar('\n');
			return (1); /* Return 1 to indicate successful command execution */
		}

		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/"); /* Change to OLDPWD or "/" if available */
	}
	else
		chdir_ret = chdir(info->argv[1]); /* Change to the specified directory */

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024)); /* Update PWD and OLDPWD after successful change */
	}
	return (0); /* Return 0 to indicate successful command execution */
}

/**
 * _myhelp - Display help information for the shell.
 * @info: Pointer to the shell's info_t structure.
 *
 * Return: Always returns 0.
 */
int _myhelp(info_t *info)
{
	(void)info; /* Avoid unused parameter warning */
	_puts("help call works. Function not yet implemented\n");
	return (0); /* Return 0 to indicate successful command execution */
}

