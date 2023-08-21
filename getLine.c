#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: structure parameter
 * @buf: buffr address
 * @len: lenght var address
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	/* If buffer is empty, fill it */
	if (!*len)
	{
		free(*buf); /* Free the previous buffer */
		*buf = NULL;
		signal(SIGINT, sigintHandler);/* Set signal handler */
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);/* Read input */
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			/* Remove trailing newline */
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);/* Remove comments */
			build_history_list(info, *buf, info->histcount++);
			/* Check for command chain using semicolon */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line excluding the newline
 * @info: structure parameter
 *
 * Return: the read bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf;/* The ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)/* EOF */
		return (-1);
	if (len)/* Commands left in the chain buffer */
	{
		j = i;/* Init new iterator to current buf position */
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;/* Increment past nulled ';' */
		if (i >= len)
		{
			i = len = 0;/* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;/* Pass back pointer to current command */
		return (_strlen(p));/* Return length of current command */
	}

	*buf_p = buf;/* Pass back buffer from _getline() */
	return (r);/* Return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: structure parameter
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc(p, s, s ? s + k : k + 1);
	if (!new_p)/* MALLOC FAILURE! */
		return (p ? (free(p), -1) : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
