#include "main.h"

/**
 * err_string - creates error string for perror()
 * @cmd_main: Master commands struct
 * @token: the command used at the time
 *
 * Return: appropriate err_string with token appended to argv[0]
 */
char *err_string(commands_centre *cmd_main, char *token)
{
	char *err;
	size_t len;

	len = _strlen(cmd_main->exec_error) + _strlen(token) + 1;
	err = malloc(sizeof(char) * len);
	if (err == NULL)
		return (NULL);
	err = _strcpy(err, cmd_main->exec_error);
	if (err == NULL)
		return (NULL);
	err = _strconcat(err, token);
	if (err == NULL)
		return (NULL);
	return (err);
}

/**
 * set_argv - sets argv for execve
 * @token: argv[0]
 *
 * Return: Pointer to args
 */
char **set_argv(char *token)
{
	char **argv;

	argv = malloc(sizeof(char *) * 2);
	if (argv == NULL)
	{
		free(argv);
		return (NULL);
	}
	argv[0] = malloc(sizeof(char) * (_strlen(token) + 1));
	if (argv[0] == NULL)
	{
		free(argv[0]);
		free(argv);
		return (NULL);
	}
	argv[0] = _strcpy(argv[0], token);
	if (argv[0] == NULL)
	{
		free(argv[0]);
		free(argv);
		return (NULL);
	}
	argv[1] = NULL;
	return (argv);
}

