#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for reading and writing */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
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
#define USE_GETLINE 0
#define USE_STRTOK 0

/* Filename for storing shell history */
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* @environ: External environment variable array */
extern char **environ;

/**
 * struct liststr - Struc for a singly linked list node holding a str and num
 * @num: The numeric value associated with the node.
 * @str: The string value stored in the node.
 * @next: Pointer to the next node in the list.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Structure for holding shell execution information.
 * @arg: A string containing arguments from getline.
 * @argv: An array of strings generated from arg.
 * @path: The path to the current command.
 * @argc: The argument count.
 * @line_count: The line count for error tracking.
 * @err_num: Error code for exit() calls.
 * @linecount_flag: Flag to count this line of input.
 * @fname: The program filename.
 * @env: Linked list containing a local copy of environ.
 * @history: Linked list for history.
 * @alias: Linked list for aliases.
 * @env_changed: Flag indicating if environ was changed.
 * @status: Return status of the last executed command.
 * @cmd_buf: Address of the pointer to the cmd buffer for chaining.
 * @cmd_buf_type: Type of command chaining (CMD_OR, CMD_AND, CMD_CHAIN).
 * @readfd: File descriptor for reading line input.
 * @histcount: History line number count.
 * @environ: External environment variable array
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

	char **cmd_buf; /*Pointer to cmd buffer for chaining*/
	int cmd_buf_type; /* Command chaining type.*/
	int readfd;
	int histcount;
} info_t;

/*Initialize info_t structure*/
#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - Structure for built-in command and related function.
 * @type: The string indicating the built-in command.
 * @func: Pointer to the function implementing the built-in command.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Declarations of functions defined in toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* Declarations of functions defined in toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* Declarations of functions defined in loophsh.c */
int loophsh(char **);

/* Declarations of functions defined in toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* Declarations of functions defined in toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* Declarations of functions defined in string1.c */
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
void _puts(const char *str);
int _putchar(char c);

/* Declarations of functions defined in toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Declarations of functions defined in toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(const char *str, const char *delim);

/* Declarations of functions defined in toem_realloc.c */
void *mem_fill(void *s, char b, unsigned int n);
void free_strings(char **strings);
void *realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size);

/* Declarations of functions defined in toem_memory.c */
int safe_free(void **ptr);

/* Declarations of functions defined in toem_atoi.c */
int interactive(const info_t *info);
int is_delim(char c, const char *delim);
int _isalpha(int c);
int _atoi(const char *s);

/* Declarations of functions defined in toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Declarations of functions defined in toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* Declarations of functions defined in toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* Declarations of functions defined in toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* Declarations of functions defined in toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Declarations of functions defined in toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* Declarations of functions defined in toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* Declarations of functions defined in toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Declarations of functions defined in toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* Declarations of functions defined in toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Declarations of functions defined in toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
