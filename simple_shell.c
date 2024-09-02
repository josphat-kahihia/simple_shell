#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point of the shell program.
 * Return: Always 0.
 */
int main(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t nread;
    pid_t pid;
    int status;

    while (1)
    {
        /* Display prompt */
        write(STDOUT_FILENO, "#cisfun$ ", 9);

        /* Read input */
        nread = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (nread == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (nread == 0)  /* EOF */
        {
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        }
        buffer[nread - 1] = '\0';  /* Remove newline character */

        /* Fork a new process */
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            /* Child process */
            execlp(buffer, buffer, NULL);
            /* If execlp returns, it must have failed */
            perror(buffer);
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent process */
            waitpid(pid, &status, 0);
        }
    }

    return (EXIT_SUCCESS);
}

