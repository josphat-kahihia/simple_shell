#ifndef MAIN_H
#define MAIN_H

/* ========================= Standard libraries ============================ */
#include <stdlib.h>
#include <stdio.h> /* For debugging printfs. Will remove later */
#include <unistd.h>
#include <string.h> /* For strtok, will remove later */
#include <sys/wait.h> /* For waitpid() */


/* ========================= Structs and Typedefs ========================== */
/**
 * struct command_string - a typedef'd struct for holding a single command.
 * @argv: Array of it's arguments.
 * @string: The command string, unmodified.
 * @ac: The number of args in argv.
 * @rv: The return value of the executed command.
 * @dependency: The dependency of the command, i.e `&&` or `||` or `;`.
 * @next: A pointer to the next command.
 * @prev: A pointer to the previous command.
 */
typedef struct command_string
{
	char **argv;
	char *string;
	int ac;
	short rv;
	short dependency;
	struct command_string *next;
	struct command_string *prev;
} command;

/**
 * struct variables - The Shell Variables
 * @string: The "key=value" string
 * @key: The "key"
 * @value: The "value"
 * @next: The next variable
 */
typedef struct variables
{
	char *string;
	char *key;
	char *value;
	struct variables *next;
} variables;

/**
 * env_var - the environment variables
 */
typedef variables env_var;

/**
 * shell_var - the shell variables
 *
 * Examples: $$, $?, user added/defined vars eg $HELLO
 */
typedef variables shell_var;

/**
 * alias_var - the aliases
 *
 * Note: The aliases self destruct i.e clear on closing the shell
 */
typedef variables alias_var;

/**
 * struct path_variables - splitted path names
 * @path_name: An individual path
 * @next: The next pathname (linked list)
 */
typedef struct path_variables
{
	char *path_name;
	struct path_variables *next;
} path_var;

/**
 * struct commands_centre - a typedef'd struct for managing all commands.
 * @head: The first command string.
 * @end: The last command string, for efficiency purposes.
 * @filename: The name of the file if (mode == 2), null if otherwise.
 * @execname: argv[0] of the shell executable
 * @exec_error: ("%s:", argv[0])
 * @cl: The literal input string from getline() - the command line.
 * @lc: The current line of execution - line count.
 * @cc: The number of commands in the command_line - command count.
 * @fd: The file descriptor. Either 0 for stdin or > 2 if a user-defined file.
 * @mode: The mode of execution. Either 0, 1, or 2 for tty, !tty, and file.
 */
typedef struct commands_centre
{
	command **head;
	command **end;
	char **cl;
	char *filename;
	char *execname;
	char *exec_error;
	int lc;
	int cc;
	int fd;
	int mode;
} commands_centre;

/**
 * struct variables_centre - a typedef'd struct for managing all variables
 * @env_head: Pointer to the first env var
 * @env_end: Pointer to the last env var
 * @shell_head: Pointer to the first shell var, presumably `$$`
 * @shell_end: Pointer to the last shell var
 * @alias_head: Pointer to the first alias var
 * @alias_end: Pointer to the last alias var
 * @path_head: Pointer to first pathname, obtained from env
 * @cwd: path of the current working directory
 * @owd: path of the most recent working directory
 * @execname: argv[0] of the shell executable
 * @exec_error: ("%s:", argv[0])
 */
typedef struct variables_centre
{
	env_var **env_head;
	env_var **env_end;
	shell_var **shell_head;
	shell_var **shell_end;
	alias_var **alias_head;
	alias_var **alias_end;
	path_var **path_head;
	char *cwd;
	char *owd;
	char *execname;
	char *exec_error;
} variables_centre;

/* ===================== function declarations ==============================*/
/*
 * Function Declarations - All function prototypes used in this program
 *
 * Purpose: This comment block mentions where the functions have been defined,
 * in order of the files (purpose).
 *
 * Intrepretation: Functions whose arguments are denoted by a `*` have
 * multiple definitions. All unused versions and deprecated functions are
 * commented out. A function that has multiple definitions in various filenames
 * is denoted by `filename , [filename...]` is to be handled very carefully.
 * Only one of those files can be compiled by GCC. Multiple occurences should
 * only occur in development. A function whose name is `[undefined]` is a
 * function that has not yet been defined in a file. Same goes for `status:
 * not started` for a majority of them. A function which has two filenames
 * separated by a `>` sign such as `filename > [filename]` indicates that
 * the function should be moved to the `[filename]` mentioned.
 *
 * Note: Any function that has been commented out with no matching reason
 * above is taken to be deprecated and removed from the source code. It is
 * only mentioned for reference purposes.
 * ============================================================================
 *
 * ---- main.c ----
 * @main(*) - main.c | status: CI/CD - in development
 *
 * ---- init.c ----
 * @init_commands_centre() - init.c | status: finished
 *
 * ---- input.c ----
 * @_getline() - input.c | status: finished
 * @prompt() - input.c | status: finished
 * @get_input() - input.c | status: in development
 *
 * ---- input-utils.c ----
 * @realloc_g_buff() - input-utils.c | status: finished
 * @_getline_helper() - input-utils.c | status: finished/untested
 * @_getline_setter() - input-utils.c | status: finished/untested
 *
 * ---- parser.c ----
 * @extract_commands() - parser.c | status: CI/CD - finished
 *
 * ---- exec.c ----
 * @execute_commands() - exec.c | status: in development
 *
 * ---- exec-utils.c ----
 * @err_string() - exec-utils.c | status: in development
 * @set_argv() - exec-utils.c | status: in development
 *
 * ---- memory-utils.c ----
 * @_realloc() - memory-utils.c | status: finished
 *
 * ---- sting-utils.c ----
 * @_strlen() - string-utils.c | status: finished
 * @get_substring() - string-utils.c | finished
 * @_strcpy() - string-utils.c | status: finished
 * @_strconcat() - string-utils.c | status: finished
 *
 * ============================================================================
 */
/* int main(void); */
/* int main(int ac, char **argv); */
int main(int ac, char **argv, char **env);
/* init.c */
commands_centre *init_commands_centre(char *execname);
/* input.c */
ssize_t _getline(char **linepointer, size_t *n, int fd);
void prompt(char *s);
ssize_t get_input(commands_centre *cmd_main);
/* input-utils.c */
char *realloc_g_buff(char *s, size_t *size);
char *_getline_helper(char **lp, char *i, char *mark);
ssize_t _getline_setter(char *mark, char *i, ssize_t rv, ssize_t br);
/* parser.c */
char *extract_commands(commands_centre *cmd_main);
/* exec.c */
int execute_commands(commands_centre *cmd_main, char *token, char **env);
/* exec-utils.c */
char *err_string(commands_centre *cmd_main, char *token);
char **set_argv(char *token);
/* mem-utils.c */
void *_realloc(void *ptr, size_t size);
/* string-utils.c */
size_t _strlen(char *s);
char *get_substring(char *start, char *end);
char *_strcpy(char *dest, const char *src);
char *_strconcat(char *dest, char *src);

#endif /* main.h */
