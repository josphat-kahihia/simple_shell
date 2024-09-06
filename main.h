#ifndef MAIN_H
#define MAIN_H

/* Standard libraries */
#include <stdlib.h>
#include <stdio.h> /* For debugging printfs. Will remove later */
#include <unistd.h>

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
 * struct commands_centre - a typedef'd struct for managing all commands.
 * @head: The first command string.
 * @end: The last command string, for efficiency purposes.
 * @filename: The name of the file if (mode == 2), null if otherwise.
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
	int lc;
	int cc;
	int fd;
	int mode;
} commands_centre;

/**
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
 * @main(*) - main.c | status: in development
 *
 * ---- init.c ----
 * @init_commands_centre() - init.c | status: finished
 *
 * ---- input.c ----
 * @_getline() - input.c | status: finished
 * @prompt() - input.c | status: finished
 *
 * ---- input-utils.c ----
 * @realloc_g_buff() - input-utils.c | status: finished
 *
 * ---- parser.c ----
 * @extract_commands() - [undefined] > parser.c | status: not started
 *
 * ---- memory-utils.c ----
 * @_realloc() - memory-utils.c | status: finished
 *
 * ---- sting-utils.c ----
 * @_strlen() - string-utils.c | status: finished
 * @get_substring() - string-utils.c | finished
 * @_strcpy() - string-utils.c | status: finished
 * @_strconcat() - string-utils.c | status: not started
 *
 * ============================================================================
 *
 * Return: nothing - literally here to appease betty
 */
int main(void);
/* int main(int ac, char **argv); */
/* int main(int ac, char **argv, char **env); */
/* init.c */
commands_centre *init_commands_centre();
/* input.c */
ssize_t _getline(char **linepointer, size_t *n, int fd);
void prompt(char *s);
/* input-utils.c */
char *realloc_g_buff(char *s, size_t *size);
/* parser.c */
int extract_commands(commands_centre *cmd_main);
/* mem-utils.c */
void *_realloc(void *ptr, size_t size);
/* string-utils.c */
size_t _strlen(char *s);
char *get_substring(char *start, char *end);
char *_strcpy(char *dest, const char *src);
char *_strconcat(char *dest, char *src);

#endif /* main.h */
