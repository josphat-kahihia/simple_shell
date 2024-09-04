#include "shell.h"

int execute_command(char **args)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
    {
        /* An empty command was entered. */
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("shell");
    }
    else
    {
        /* Parent process */
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (1);
}

