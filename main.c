#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
    char *input = NULL;
    size_t len = 0;
    ssize_t read;

    (void)argc; /* unused */
    (void)argv; /* unused */

    while (1)
    {
        /* Display prompt */
        write(STDOUT_FILENO, "$ ", 2);

        /* Get user input */
        read = getline(&input, &len, stdin);
        if (read == -1)
        {
            if (feof(stdin))
            {
                free(input);
                exit(EXIT_SUCCESS);
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }

        /* Remove newline character */
        if (input[read - 1] == '\n')
        {
            input[read - 1] = '\0';
        }

        /* Execute command */
        execute_command(input);
    }

    return (EXIT_SUCCESS);
}

