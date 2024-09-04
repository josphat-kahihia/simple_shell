#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;

    while (1) /* Infinite loop to keep the shell running */
    {
        printf("$ "); /* Display the prompt */
        if (getline(&line, &len, stdin) == -1)
        {
            perror("getline");
            free(line);
            exit(EXIT_FAILURE);
        }

        printf("You entered: %s", line); /* Just print what was entered for now */
    }

    free(line); /* Free the allocated memory */
    return 0;
}
