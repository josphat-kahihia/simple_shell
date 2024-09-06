#include "main.h"

/**
 * extract_commands - extract the token
 * @cmd_main: commands centre
 * @token: a token
 *
 * Return: Pointer to the token
 */
char *extract_commands(commands_centre *cmd_main)
{
	char *cmd_line;
	char *token;

	cmd_line = malloc(sizeof(char) * (_strlen(*cmd_main->cl) + 1));
	cmd_line = _strcpy(cmd_line, *cmd_main->cl);
	token = strtok(cmd_line, "\n");
	if (token == NULL)
		return (NULL);
	return (token);
}
