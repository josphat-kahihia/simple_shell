#include "main.h"

/**
 * extract_commands - extract the token
 * @cmd_main: commands centre
 *
 * Return: Pointer to the token
 */
char **extract_commands(commands_centre *cmd_main)
{
	char **argv;
	char *cmd_line;
	char *token;
	size_t tokens;
	size_t i;

	i = 0;
	tokens = 64;
	cmd_line = malloc(sizeof(char) * (_strlen(*cmd_main->cl) + 1));
	cmd_line = _strcpy(cmd_line, *cmd_main->cl);
	token = strtok(cmd_line, "\n");
	if (token == NULL)
		return (NULL);
	argv = malloc(sizeof(char *) * tokens);
	token = strtok(token, " ");
	while (token != NULL)
	{
		argv[i] = token;
		if (i > (tokens - tokens/3))
		{
			tokens *= 2;
			argv = _realloc(argv, (sizeof(char *) * tokens));
		}
		token = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
