#include "general.h"
#include "shell.h"

/**
 * main - Entry point for the shell program
 *
 * @argc: Number of input arguments
 * @argv: Array of input arguments
 *
 * Return: 0 if successful, 1 if an error occurs
 */
int main(int argc, char **argv)
{
    general_t *shell_info;
    int exit_code;

    shell_info = malloc(sizeof(general_t));
    if (shell_info == NULL)
    {
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }

    shell_info->pid = getpid();
    shell_info->status_code = 0;
    shell_info->n_commands = 0;
    shell_info->argc = argc;
    shell_info->argv = argv;
    shell_info->mode = isatty(STDIN_FILENO) ? INTERACTIVE : NON_INTERACTIVE;
    
    start(shell_info);

    exit_code = shell_info->status_code;

    free(shell_info);

    return (exit_code);
}
