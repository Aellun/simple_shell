#include "shell.h"
/**
 * main - Entry point to Unix shell program.
 * @ac: Argument count
 * @av: Argument vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT }; /*initiate info structure array*/
	int fd = 2;

	asm(/* Manipulate fd using inline assembly */
			"mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd)
	    );
	/* Check for command-line argument */
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);/*Attempt to open the specified file*/
		if (fd == -1)
		{
			if (errno == EACCES)/*Handle different error cases*/
			{
				exit(126);/*Exit with status 126 for permission error */
			}
			if (errno == ENOENT)
			{/*Print err msg for file not found*/
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);/* Exit with status 127 for file not found*/
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;/* Set readfd in info structure */
	}
	populate_env_list(info);/*Populate environ list and read command hist*/
	read_history(info);
	hsh(info, av);/*Start the shell program*/
	return (EXIT_SUCCESS);
}

