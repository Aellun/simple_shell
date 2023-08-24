#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

/* Buffer sizes for reading and writing */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining types */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Conversion flags for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Flag indicating whether to use system getline() */
#define USE_STRTOK 0
#define USE_GETLINE 0

/* Filename for storing shell history */
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* External environment variable array */
extern char **environ;

/**
 * struct liststr - Struct for a singly linked list node holding a str and num
 * @num: The numeric value linked with the node.
 * @str: The str value stored in the node.
 * @next: Pointer to the next node in the list.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Struct to hold shell execution info.
 * @arg: A str containing args from getline.
 * @argv: An array of strings generated from arg.
 * @path: The path to the current command.
 * @argc: The arg count.
 * @line_count: The line count for error tracking.
 * @err_num: Error code for exit() calls.
 * @linecount_flag: Flag to count this line of input.
 * @fname: The program filename.
 * @env: Linked list containing a local copy of environment.
 * @history: Linked list for history.
 * @alias: Linked list for aliases.
 * @environ: External environment variable array.
 * @env_changed: Flag indicating if environ was changed.
 * @status: Return status of the last executed command.
 * @cmd_buf: Address of the pointer to the cmd buffer for chaining.
 * @cmd_buf_type: Type of command chains (CMD_OR, CMD_AND, CMD_CHAIN).
 * @readfd: File descriptor for reading line input.
 * @histcount: History line number count.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* Pointer to cmd buffer for chaining */
	int cmd_buf_type; /* Command chaining type */
	int readfd; /* File descriptor for reading line input */
	int histcount; /* History line number count */
} info_t;

/* Initialize info_t structure */
#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, \
	NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct builtin - Struct for built-in command & related function.
 * @type: The str indicating the built-in command.
 * @func: Pointer to the function implementing the built-in command.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Declarations of functions defined in atoi.c */
int interactive(const info_t *info);
int is_delim(char c, const char *delim);
int _isalpha(int c);
int _atoi(const char *s);

/* Declarations of functions defined in builtin.c*/
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

/* Declarations of functions defined in builtin1.c */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str)
	int print_alias(list_t *node);
	int _myalias(info_t *info);

	/* Declarations of functions defined in errors1.c */
	int _erratoi(char *s);
	void print_error(info_t *info, char *estr);
	int print_d(int input, int fd);
	void remove_comments(char *);
	char *convert_number(long int num, int base, int flags);

	/* Declarations of functions defined in errors.c */
	void _eputs(char *str);
	int _eputchar(char c);
	int _putfd(char c, int fd);
	int _putsfd(char *str, int fd);

	/* Declarations of functions defined in getenv.c */
	char **get_environ(info_t *info);
	int _unsetenv(info_t *info, char *var);
	int _setenv(info_t *info, char *var, char *value);

	/* Declarations of functions defined in getline.c */
	ssize_t input_buf(info_t *info, char **buf, size_t *len);
	ssize_t get_input(info_t *info);
	ssize_t read_buf(info_t *info, char *buf, size_t *i);
	int _getline(info_t *info, char **ptr, size_t *length);
	void sigintHandler(__attribute__((unused)) int sig_num);

	/* Declarations of functions defined in history.c */
	char *_getenv(info_t *info, const char *name);
	size_t _strlen(const char *s);
	char *_strcpy(char *dest, const char *src);
	char *_strcat(char *dest, const char *src);
	void _putsfd(const char *str, ssize_t fd);
	void _putfd(char c, ssize_t fd);
	void add_node_end(list_t **head, char *str, int num);
	void delete_node_at_index(list_t **head, unsigned int index);

	/* Declarations of functions defined in lists.c */
	list_t *add_node(list_t **head, const char *str, int num);
	list_t *add_node_end(list_t **head, const char *str, int num);
	size_t print_list_str(const list_t *h);
	int delete_node_at_index(list_t **head, unsigned int index);
	void free_list(list_t **head_ptr);

	/* Declarations of functions defined in memory.c */
	int safe_free(void **ptr);

	/* Declarations of functions defined in string.c */
	int _strlen(char *s);
	int _strcmp(char *s1, char *s2);
	char *starts_with(const char *haystack, const char *needle);
	char *_strcat(char *dest, char *src);

	/* Declarations of functions defined in string1.c */
	char *_strcpy(char *dest, const char *src);
	char *_strdup(const char *str);
	void _puts(const char *str);
	int _putchar(char c);

	/* Declarations of functions defined in tokenizer.c */
	char **strtow(char *str, char *d);
	char **strtow2(char *str, char d);

	/* Declarations of functions defined in vars.c */
	int is_delimiter(info_t *info, char *buf, size_t *p);
	void check_delimiter(info_t *info, char *buf, size_t *p, size_t i, size_t len);
	int replace_alias(info_t *info);
	int replace_variables(info_t *info);
	int replace_string(char **old, char *new);

	/* Declarations of functions defined in shell_loop.c */
	char *get_user_input(void);
	void fork_cmd(info_t *info);

	/* Declarations of functions defined in realloc.c */
	void *mem_fill(void *s, char b, unsigned int n);
	void free_strings(char **strings);
	void *realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size);

	/* Declarations of functions defined in parser.c */
	int is_cmd(info_t *info, char *path);
	char *dup_chars(char *pathstr, int start, int stop);
	char *find_path(info_t *info, char *pathstr, char *cmd);

	/* Declarations of functions defined in main.c */
	int is_cmd(info_t *info, char *path);
	char *dup_chars(char *pathstr, int start, int stop);
	char *find_path(info_t *info, char *pathstr, char *cmd);
	int main(int ac, char **av);

	/* Declarations of functions defined in list1.c */
	size_t list_len(const list_t *h);
	char **list_to_strings(list_t *head);
	size_t print_list(const list_t *h);
	list_t *node_starts_with(list_t *node, char *prefix, char c);
	ssize_t get_node_index(list_t *head, list_t *node);

	/* Declarations of functions defined in exit.c*/
	char *_strncpy(char *dest, char *src, int n);
	char *_strncat(char *dest, char *src, int n);
	char *_strchr(char *s, char c);

	/* Declarations of functions defined in environ.c*/
	int _myenv(info_t *info);
	char *_getenv(info_t *info, const char *name);
	int _mysetenv(info_t *info);
	int _myunsetenv(info_t *info);
	int populate_env_list(info_t *info);

	/* Declarations of functions defined in get_info.c*/
	void clear_info(info_t *info);
	void set_info(info_t *info, char **av);
	void free_info(info_t *info, int all);
#endif /* _SHELL_H_ */

