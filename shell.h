#ifndef MY_SHELL_H
#define MY_SHELL_H

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

/* for read/write buffers */
#define MY_READ_BUF_SIZE 1024
#define MY_WRITE_BUF_SIZE 1024
#define MY_BUF_FLUSH -1

/* for command chain */
#define MY_CMD_NORM     0
#define MY_CMD_OR       1
#define MY_CMD_AND      2
#define MY_CMD_CHAIN    3

/* for conversion */
#define MY_CONVERT_LOWERCASE   1
#define MY_CONVERT_UNSIGNED    2

/* 1 if using system getline() */
#define MY_USE_GETLINE  0
#define MY_USE_STRTOK   0

#define MY_HIST_FILE     ".my_shell_history"
#define MY_HIST_MAX      4096

extern char **environ;

/**
* struct my_liststr - singly linked list
* @num: the number field
* @str: a string
* @next: points to the next node
*/
typedef struct my_liststr
{
	int num;

	char *str;

	struct my_liststr *next;
} my_list_t;

/**
* struct my_passinfo - contains pseudo-arg to pass into a func
*                     allowing uniform prototype for function pointer struct
* @arg: a string generated from getline containing arguments
* @argv: an array of strings generated from arg
* @path: a string path for the current command
* @argc: the argument count
* @line_count: the error count
* @err_num: the error code for exit()s
* @linecount_flag: if on count this line of input
* @fname: the program filename
* @env: linked list local copy of environ
* @history: history of cmd
* @alias: the alias node
* @my_environ: custom modified copy of environ from LL env
* @env_changed: on if environ was changed
* @status: the return status of the last exec'd command
* @cmd_buf: address of pointer to cmd_buf, on if chaining
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: the fd from which to read line input
* @histcount: the history line number count
*/
typedef struct my_passinfo
{
	char *arg;

	char **argv;

	char *path;

	int argc;

	unsigned int line_count;

	int err_num;

	int linecount_flag;

	char *fname;

	my_list_t *env;
	my_list_t *history;
	my_list_t *alias;
	char **my_environ;

	int env_changed;

	int status;

	char **cmd_buf;

	int cmd_buf_type;

	int readfd;

	int histcount;

} my_info_t;

#define MY_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
* struct my_builtin - contains a builtin string and related function
* @type: the builtin command flag
* @func: the function
*/
typedef struct my_builtin
{
	char *type;

	int (*func)(my_info_t *);
} my_builtin_table;

/* my_shell.c */
int my_shell(my_info_t *, char **);
int find_builtin(my_info_t *);
void find_cmd(my_info_t *);
void fork_cmd(my_info_t *);

/* my_search_path.c */
int is_cmd(my_info_t *, char *);
char *dup_chars(char *, int, int);
char *find_my_path(my_info_t *, char *, char *);

/* my_error_string_functions.c */
void _my_eputs(char *);
int _my_eputchar(char);
int _my_putfd(char c, int fd);
int _my_putsfd(char *str, int fd);

/* my_string_functions.c */
int _my_strlen(char *);
int _my_strcmp(char *, char *);
char *my_starts_with(const char *, const char *);
char *_my_strcat(char *, char *);

/* my_string_functions2.c */
char *_my_strcpy(char *, char *);
char *_my_strdup(const char *);
void _my_puts(char *);
int _my_putchar(char);

/* my_string_functions3.c */
char *_my_strncpy(char *, char *, int);
char *_my_strncat(char *, char *, int);
char *_my_strchr(char *, char);

/* my_string_functions4.c */
char **my_strtow(char *, char *);
char **my_strtow2(char *, char);

/* my_memory_functions.c */
char *_my_memset(char *, char, unsigned int);
void my_ffree(char **);
void *_my_realloc(void *, unsigned int, unsigned int);

/* my_memory_functions2.c */
int my_bfree(void **);

/* my_more_functions.c */
int my_interactive(my_info_t *);
int my_is_delim(char, char *);
int my_isalpha(int);
int my_atoi(char *);

/* my_more_functions2.c */
int my_erratoi(char *);
void my_print_error(my_info_t *, char *);
int my_print_d(int, int);
char *my_convert_number(long int, int, int);
void my_remove_comments(char *);

/* sbuiltin_emulators.c */
int _my_exit(my_info_t *);
int _my_cd(my_info_t *);
int _my_help(my_info_t *);

/* sbuiltin_emulators2.c */
int _my_history(my_info_t *);
int _my_alias(my_info_t *);

/* sgetline.c modules */
ssize_t get_input(my_info_t *);
int _my_getline(my_info_t *, char **, size_t *);
void sigintHandler(int);

/** sinfo.c modules */
void clear_info(my_info_t *);
void set_info(my_info_t *, char **);
void free_info(my_info_t *, int);

/* senv.c modules */
char *_my_getenv(my_info_t *, const char *);
int _my_env(my_info_t *);
int _my_setenv(my_info_t *);
int _my_unsetenv(my_info_t *);
int populate_env_list(my_info_t *);

/* senv2.c modules */
char **get_environ(my_info_t *);
int _unsetenv(my_info_t *, char *);
int _setenv(my_info_t *, char *, char *);

/* sfile_io_functions.c */
char *get_history_file(my_info_t *info);
int write_history(my_info_t *info);
int read_history(my_info_t *info);
int build_history_list(my_info_t *info, char *buf, int linecount);
int renumber_history(my_info_t *info);

/* sliststr.c modules */
my_list_t *add_node(my_list_t **, const char *, int);
my_list_t *add_node_end(my_list_t **, const char *, int);
size_t print_list_str(const my_list_t *);
int delete_node_at_index(my_list_t **, unsigned int);
void free_list(my_list_t **);

/* sliststr2.c modules */
size_t list_len(const my_list_t *);
char **list_to_strings(my_list_t *);
size_t print_list(const my_list_t *);
my_list_t *node_starts_with(my_list_t *, char *, char);
ssize_t get_node_index(my_list_t *, my_list_t *);

/* schain.c */
int is_chain(my_info_t *, char *, size_t *);
void check_chain(my_info_t *, char *, size_t *, size_t, size_t);
int replace_alias(my_info_t *);
int replace_vars(my_info_t *);
int replace_string(char **, char *);

#endif
