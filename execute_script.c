#include "shell.h"

void execute_script(char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **args;
    int status;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        args = parse_line(line);
        status = execute_command(args);

        free(args);
        if (!status)
            break;
    }

    free(line);
    fclose(fp);
}

