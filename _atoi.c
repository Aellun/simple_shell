#include "shell.h"

/**
 * interactive - Check if the shell is in interactive mode.
 * @info: Pointer to the shell's info_t structure.
 *
 * Return: 1 if it is in interactive mode, or 0 if otherwise.
 */
int interactive(const info_t *info)
{
/**
 * Check if the shell is running interactively
 * and if the read file descriptor is within a valid range.
 */
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if c is a delimiter, 0 otherwise.
 */
int is_delim(char c, const char *delim)
{
	while (*delim)
	{
		/*Compare the current char with each delimiter in the delimiter string*/
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _isalpha - Check if a character is an alphabetic character.
 * @c: The character to check.
 *
 * Return: 1 if c is an alphabetic character, 0 otherwise.
 */
int _isalpha(int c)
{
	/*Check if the char is within range of lower or upper case alphabetic char*/
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in string, the converted number otherwise.
 */
int _atoi(const char *s)
{
	int k = 0;
	int sign = 1;
	int result = 0;

	/* Handle negative numbers by checking for a leading '-' character. */
	if (s[k] == '-')
	{
		sign = -1;
		k++;
	}

	/* Convert the string of digits to an integer. */
	while (s[k] >= '0' && s[k] <= '9')
	{
		result = result * 10 + (s[k] - '0');
		k++;
	}

	/* Apply the sign and return the final result. */
	return (result * sign);
}

