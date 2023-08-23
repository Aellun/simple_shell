#include "shell.h"

/**
 * **strtow - breaks a str into words. Repeat delimiters are ignored
 * @str: the inputted string
 * @d: the delimiter string
 * Return: a ptr to an array of strings, or NULL on not success
 */
char **strtow(char *str, char *d)
{
	int x, y, z, n, num_words = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
		while (is_delim(str[x], d))
			x++;
		z = 0;
		while (!is_delim(str[x + z], d) && str[x + z])
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < z; n++)
			s[y][n] = str[x++];

		s[y][n] = '\0';
	}
	s[y] = NULL;
	return (s);
}

/**
 * **strtow2 - breaks a string into words
 * @str: the inputted string
 * @d: the delimiter
 * Return: a ptr to an array of str, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int x, y, z, n, num_words = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
				(str[x] != d && !str[x + 1]) || str[x + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		z = 0;
		while (str[x + z] != d && str[x + z] && str[x + z] != d)
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < z; n++)
			s[y][n] = str[x++];
		s[y][n] = '\0';
	}
	s[y] = NULL;
	return (s);
}

