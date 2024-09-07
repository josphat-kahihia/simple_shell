#include "main.h"

/**
 * init_commands_centre - create a commands_centre
 * @execname: [temporary] name of the sh executable
 *
 * Note: Currently modified to hold the error name. That is supposed to be
 * done by variables_centre. Move on completion of init_variables_centre()
 *
 * Return: The command centre
 */
commands_centre *init_commands_centre(char *execname)
{
	commands_centre *cmd_main;

	cmd_main = malloc(sizeof(commands_centre));
	if (cmd_main == NULL)
		return (NULL);
	cmd_main->head = NULL;
	cmd_main->end = NULL;
	cmd_main->filename = NULL;
	cmd_main->execname = execname;
	cmd_main->exec_error = malloc(sizeof(char) * (_strlen(execname) + 3));
	if (cmd_main->exec_error == NULL)
		return (NULL);
	cmd_main->exec_error = _strcpy(cmd_main->exec_error, execname);
	if (cmd_main->exec_error == NULL)
		return (NULL);
	cmd_main->exec_error = _strconcat(cmd_main->exec_error, ": ");
	if (cmd_main->exec_error == NULL)
		return (NULL);
	cmd_main->cl = NULL;
	cmd_main->lc = 0;
	cmd_main->cc = 0;
	cmd_main->fd = STDIN_FILENO;
	cmd_main->mode = 0;
	return (cmd_main);
}
