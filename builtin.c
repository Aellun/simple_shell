#include "shell.h"

/**
 * _myexit - Exit shell with a given status
 * @info: ptr to the shell info_t struct.
 * Return: Always returns -2 to show shell terminiation
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
 * _mycd - Changes shell current dir to another
 * @info: ptr to shell info_t struct
 */
int _mycd(info_t *info)
{
	char *cwd, *target_dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure emsg here<<\n");/*Add err handling failure*/
	if (!info->argv[1]) /* If no target directory provided */
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)/*Change to HOME or PWD if available*/
			chdir_ret = chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_ret = chdir(target_dir); /* Change to the target directory */
	}
	else if (_strcmp(info->argv[1], "-") == 0)/*If target directory is "-" */
	{
		if (!_getenv(info, "OLDPWD=")) /*If OLDPWD is not set*/
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');/*Change to OLDPWD or "/" if available*/
		chdir_ret = chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
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
		_setenv(info, "PWD", getcwd(buffer, 1024)); /*Update PWD and OLDPWD*/
	}
	return (0); /* Return 0 to indicate successful command execution */
}
/**
 * _myhelp - show shell-help info
 * @info: Ptr to the struc of the shell
 * Return: returns 0
 */
int _myhelp(info_t *info)
{
	(void)info; /* Avoid unused parameter warning */
	_puts("help call works. Function not yet implemented\n");
	return (0); /* Return 0 to indicate successful command execution */
}

