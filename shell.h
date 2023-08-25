#ifndef _MODIFIED_SHELL_H_
#define _MODIFIED_SHELL_H_

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
#define MOD_READ_BUFFER_SIZE 1024
#define MOD_WRITE_BUFFER_SIZE 1024
#define MOD_BUFFER_FLUSH -1

/* for command chaining */
#define MOD_COMMAND_NORMAL 0
#define MOD_COMMAND_OR 1
#define MOD_COMMAND_AND 2
#define MOD_COMMAND_CHAIN 3

/* for convert_number() */
#define MOD_CONVERT_LOWERCASE 1
#define MOD_CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define MOD_USE_GETLINE 0
#define MOD_USE_STRTOK 0

#define MOD_HISTORY_FILE ".modified_shell_history"
#define MOD_HISTORY_MAX 4096

extern char **mod_environment;

/**
 * struct modified_linked_string - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct modified_linked_string
{
	int num;
	char *str;
	struct modified_linked_string *next;
} modified_linked_list_t;

/**
 * struct modified_command_info - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for the function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @error_number: the error code for exit()s
 * @count_line: if on, count this line of input
 * @filename: the program filename
 * @env_list: linked list local copy of environment
 * @custom_environment: custom modified copy of environment from LL env
 * @command_history: the history node
 * @command_alias: the alias node
 * @environment_changed: on if environment was changed
 * @command_status: the return status of the last exec'd command
 * @command_buffer: address of a pointer to command_buffer, on if chaining
 * @command_buffer_type: command_type ||, &&, ;
 * @read_file_descriptor: the fd from which to read line input
 * @history_count: the history line number count
 */
typedef struct modified_command_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_number;
	int count_line;
	char *filename;
	modified_linked_list_t *env_list;
	modified_linked_list_t *command_history;
	modified_linked_list_t *command_alias;
	char **custom_environment;
	int environment_changed;
	int command_status;

	char **command_buffer; /* pointer to command_buffer ; chain buffer, for memory management */
	int command_buffer_type; /* command_type ||, &&, ; */
	int read_file_descriptor;
	int history_count;
} modified_command_info_t;

#define MOD_INFO_INITIALIZE	\
	{	\
	NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0,	\
	NULL, 0, 0, 0	\
	}

/**
 * struct modified_builtin_command - contains a modified builtin command string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct modified_builtin_command
{
	char *type;
	int (*func)(modified_command_info_t *);
} modified_builtin_table;

/* modified_shell_loop.c */
int mod_hsh(modified_command_info_t *, char **);
int mod_find_builtin(modified_command_info_t *);
void mod_find_command(modified_command_info_t *);
void mod_fork_command(modified_command_info_t *);

/* modified_parser.c */
int mod_is_command(modified_command_info_t *, char *);
char *mod_duplicate_characters(char *, int, int);
char *mod_find_path(modified_command_info_t *, char *, char *);

/* modified_loop_shell.c */
int mod_loop_shell(char **);

/* modified_error_handlers.c */
void mod_error_puts(char *);
int mod_error_putchar(char);
int mod_put_fd(char c, int fd);
int mod_puts_fd(char *str, int fd);

/* modified_string_operations.c */
int mod_string_length(char *);
int mod_string_compare(char *, char *);
char *mod_starts_with(const char *, const char *);
char *mod_concatenate_strings(char *, char *);

/* modified_string_operations_1.c */
char *mod_string_copy(char *, char *);
char *mod_string_duplicate(const char *);
void mod_put_string(char *);
int mod_put_character(char);

/* modified_exit_handlers.c */
char *mod_string_copy_n(char *, char *, int);
char *mod_string_concatenate_n(char *, char *, int);
char *mod_string_find_character(char *, char);

/* modified_tokenizer.c */
char **mod_tokenize_string(char *, char *);
char **mod_tokenize_string_2(char *, char);

/* modified_dynamic_memory.c */
char *mod_memory_set(char *, char, unsigned int);
void mod_free_allocated_memory(char **);
void *mod_reallocate_memory(void *, unsigned int, unsigned int);

/* modified_memory_operations.c */
int mod_free_allocated_memory(void **);

/* modified_numeric_conversion.c */
int mod_interactive_mode(modified_command_info_t *);
int mod_is_delimiter(char, char *);
int mod_is_alpha(int);
int mod_ascii_to_integer(char *);

/* modified_error_handlers_1.c */
int mod_error_ascii_to_integer(char *);
void mod_print_error(modified_command_info_t *, char *);
int mod_print_decimal(int, int);
char *mod_convert_number(long int, int, int);
void mod_remove_comments(char *);

/* modified_builtin_commands.c */
int mod_exit(modified_command_info_t *);
int mod_change_directory(modified_command_info_t *);
int mod_help(modified_command_info_t *);

/* modified_builtin_commands_1.c */
int mod_history(modified_command_info_t *);
int mod_alias(modified_command_info_t *);

/* modified_get_line.c */
ssize_t mod_get_input(modified_command_info_t *);
int mod_get_line(modified_command_info_t *, char **, size_t *);
void mod_signal_interrupt_handler(int);

/* modified_get_info.c */
void mod_clear_information(modified_command_info_t *);
void mod_set_information(modified_command_info_t *, char **);
void mod_free_information(modified_command_info_t *, int);

/* modified_environment_operations.c */
char *mod_get_environment(modified_command_info_t *, const char *);
int mod_list_environment(modified_command_info_t *);
int mod_set_environment(modified_command_info_t *);
int mod_unset_environment(modified_command_info_t *);
int mod_populate_environment_list(modified_command_info_t *);

/* modified_get_environment.c */
char **mod_get_environment(modified_command_info_t *);
int mod_unset_environment(modified_command_info_t *, char *);
int mod_set_environment(modified_command_info_t *, char *, char *);

/* modified_command_history.c */
char *mod_get_history_file(modified_command_info_t *info);
int mod_write_history(modified_command_info_t *info);
int mod_read_history(modified_command_info_t *info);
int mod_build_history_list(modified_command_info_t *info, char *buffer, int line_count);
int mod_renumber_history(modified_command_info_t *info);

/* modified_linked_lists.c */
modified_linked_list_t *mod_add_node(modified_linked_list_t **, const char *, int);
modified_linked_list_t *mod_add_node_end(modified_linked_list_t **, const char *, int);
size_t mod_print_linked_list_strings(const modified_linked_list_t *);
int mod_delete_node_at_index(modified_linked_list_t **, unsigned int);
void mod_free_linked_list(modified_linked_list_t **);

/* modified_linked_lists_1.c */
size_t mod_linked_list_length(const modified_linked_list_t *);
char **mod_linked_list_to_strings(modified_linked_list_t *);
size_t mod_print_linked_list(const modified_linked_list_t *);
modified_linked_list_t *mod_node_starts_with(modified_linked_list_t *, char *, char);
ssize_t mod_get_node_index(modified_linked_list_t *, modified_linked_list_t *);

/* modified_variable_operations.c */
int mod_is_command_chain(modified_command_info_t *, char *, size_t *);
void mod_check_command_chain(modified_command_info_t *, char *, size_t *, size_t, size_t);
int mod_replace_alias(modified_command_info_t *);
int mod_replace_variables(modified_command_info_t *);
int mod_replace_string(char **, char *);

#endif
