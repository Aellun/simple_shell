#include "shell.h"

/**
 * interactive - is true when shell is interative
 * @info: struct address
 *
 * Return: 1 if true and 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - look if  char is delim
 * @c: char being checked
 * @delim: the delim str
 * Return: 1 if successful 0 otherwise
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _isalpha - looks for alphabetic char
 * @c: The char to input
 * Return: 1 if true 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - turn a str to an int
 * @s: str being turned
 * Return: 0 if false
 */
int _atoi(char *s)
{
	int y, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (y = 0; s[y] != '\0' && flag != 2; y++)
	{
		if (s[y] == '-')
			sign *= -1;

		if (s[y] >= '0' && s[y] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[y] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
