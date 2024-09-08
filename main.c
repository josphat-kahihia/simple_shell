#include "main.h"

/**
 * main - init, run and control the shell
 * @ac: ac
 * @argv: shell's args
 * @env: inherited env
 *
 * Description: The main function first initialises the variables 'centres'
 * required to run the shell, then checks the mode of execution, and handles
 * operation based on that mode. It should never get to its own return value.
 * That signifies an error that should be checked. However, because GCC-alx
 * requires it, we'll set it to return to zero. In the current state, it should
 * NOT get to return. (updated).
 *
 * Return: 0 on success, -1 on failure.
 */
int main(int ac, __attribute__((unused))char **argv, char **env)
{
	commands_centre *cmd_main;
	char **tokens;
	ssize_t gr;

	if (ac > 1)
		exit(-1); /* Not implemented yet */
	cmd_main = init_commands_centre(argv[0]);
	if (cmd_main == NULL)
		return (-1);
	prompt(NULL);
	gr = get_input(cmd_main);
	while (gr > 0 || *cmd_main->cl)
	{
		if (_strlen(*cmd_main->cl) == 0)
		{
			write(STDOUT_FILENO, "\n", 2);
			exit(0); /* EOF encountered */
		}
		if (_strlen(*cmd_main->cl) > 1)
		{
			tokens = extract_commands(cmd_main);
			execute_commands(cmd_main, tokens, env);
		}
		*cmd_main->cl = NULL; /* reset for EOF logic to work */
		prompt(NULL);
		gr = get_input(cmd_main);
	}
	if (gr < 0 && !(*cmd_main->cl))
		exit(-1); /* Problem with read/the getline function itself */
	return (0);
}
