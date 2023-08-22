#include "shell.h"

/**
 * count_words - count the number of words in a string
 * @str: the input string
 * @delim: the delimiter string
 * Return: number of words
 */
static int count_words(const char *str, const char *delim)
{
	int count = 0;
	int inside_word = 0;

	while (*str)
	{
		if (!strchr(delim, *str))
		{
			if (!inside_word)
			{
				inside_word = 1;
				count++;
			}
		}
		else
		{
			inside_word = 0;
		}
		str++;
	}

	return (count);
}

/**
 * get_word_length - get the length of a word
 * @str: the input string
 * @delim: the delimiter string
 * Return: length of word
 */
static int get_word_length(const char *str, const char *delim)
{
	int length = 0;

	while (*str && !strchr(delim, *str))
	{
		length++;
		str++;
	}

	return (length);
}

/**
 * copy_word - copy a word from source to destination
 * @src: the source string
 * @dst: the destination string
 * @delim: the delimiter string
 */
static void copy_word(const char *src, char *dst, const char *delim)
{
	while (*src && !strchr(delim, *src))
	{
		*dst = *src;
		src++;
		dst++;
	}
	*dst = '\0';
}

/**
 * **strtow - break a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @delim: the delimiter string
 * Return: returns a pointer to an array of strings, on failure, NULL
 */
char **strtow(const char *str, const char *delim)
{
	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (delim == NULL)
		delim = " ";

	int num_words = count_words(str, delim);

	if (num_words == 0)
		return (NULL);
	char **words = malloc((num_words + 1) * sizeof(char *));

	if (words == NULL)
		return (NULL);
	int word_index = 0;

	while (*str)
	{
		while (*str && strchr(delim, *str))
			str++;

		if (*str)
		{
			int word_length = get_word_length(str, delim);

			words[word_index] = malloc(word_length + 1);
			if (words[word_index] == NULL)
			{
				for (int i = 0; i < word_index; i++)
					free(words[i]);
				free(words);
				return (NULL);
			}
			copy_word(str, words[word_index], delim);
			str += word_length;
			word_index++;
		}
	}
	words[word_index] = NULL;
	return (words);
}

