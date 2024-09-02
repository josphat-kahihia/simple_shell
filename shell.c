#include "shell.h"

/**
 * execute_command - Executes the command provided by the user.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
    pid_t pid;
    int status;
    char *argv[2];

    argv[0] = command;
    argv[1] = NULL;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        /* Child process */
        if (execve(command, argv, NULL) == -1)
        {
            perror(command);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        waitpid(pid, &status, 0);
    }
}

