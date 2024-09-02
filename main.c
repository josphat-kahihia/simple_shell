#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

/**
 * main - Entry point of the simple shell
 *
 * Return: 0 on success, 1 on error
 */
int main(void)
{
    char *line = NULL;
    char *args[2];
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;

    while (1)
    {
        printf(PROMPT);  /* Display the prompt */
        read = getline(&line, &len, stdin);  /* Get user input */

        if (read == -1)  /* Handle EOF (Ctrl+D) */
        {
            printf("\n");
            break;
        }

        line[read - 1] = '\0';  /* Remove newline character */

        if (strcmp(line, "") == 0)  /* Skip empty input */
            continue;

        args[0] = line;  /* Command */
        args[1] = NULL;  /* No arguments */

        pid = fork();  /* Fork a child process */

        if (pid == -1)  /* Error forking */
        {
            perror("fork");
            free(line);
            exit(1);
        }
        else if (pid == 0)  /* Child process */
        {
            if (execve(args[0], args, NULL) == -1)  /* Execute command */
            {
                perror("./shell");
                exit(1);
            }
        }
        else  /* Parent process */
        {
            wait(&status);  /* Wait for child process to finish */
        }
    }

    free(line);  /* Free allocated memory */
    return 0;
}

