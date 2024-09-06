#include "main.h"

/**
 * init_commands_centre - create a commands_centre
 *
 * Return: The command centre
 */
commands_centre *init_commands_centre()
{
	commands_centre *cmd_main;

	cmd_main = malloc(sizeof(commands_centre));
	if (cmd_main == NULL)
		return (NULL);
	cmd_main->head = NULL;
	cmd_main->end = NULL;
	cmd_main->filename = NULL;
	cmd_main->command_line = NULL;
	cmd_main->line_count = 0;
	cmd_main->command_count = 0;
	/**
	 * comment this out in the current state:
	 * cmd_main->fd = STDIN_FILENO;
	 * cmd_main->mode = 0;
	 */
	return (cmd_main);
}
