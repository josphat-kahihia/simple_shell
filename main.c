#include "shell.h"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        /* Interactive mode */
        shell_loop();
    }
    else if (argc == 2)
    {
        /* Non-interactive mode */
        execute_script(argv[1]);
    }
    else
    {
        fprintf(stderr, "Usage: %s [script]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return (0);
}

