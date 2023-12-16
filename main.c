#include "myShell.h"

/**
 * main - entry point for shell
 * 
 * Return: 0 on success
 */
int main(int ac, char **arg)
{
        /**
         * 1. Create (open) a log file
         * 2. Log (write) that the shell is running
         * 
         */

        if (ac == 1) /*If no arguments are not provided [interactive]*/
                prompt(); 
        /*else if (ac >= 2)
                handle_execution(arg);
     
        /*else to handle arguments [non-interactive] mode*/
}

/**
 * prompt -prompts the user to enter command
 * 
 * Return: 0 on success
 */
int prompt()
{
        int proceed = 1;
        char *prompt;
        char *cmdStr = NULL;
        char **args = NULL;
        size_t count;
        size_t len = 0;
        ssize_t read_getline;
        ssize_t return_write;
        int return_handle_execution;
        int i;

        while (proceed == 1)
        {
                prompt = "$ ";
                count = strlen(prompt);
                return_write = write(1, prompt, count);
                if (return_write == -1)
                        perror("Error writing to stdinput");
                else if (return_write < (signed)count)
                        perror("Warning: insufficient size");

                read_getline = getline(&cmdStr, &len, stdin);

                if (read_getline != 1)
                {
                        if (_strcmp(cmdStr, "exit") == 0)
                                exit(EXIT_SUCCESS);
                        else if (cmdStr[read_getline - 1] == '\n')
                                cmdStr[read_getline - 1] = '\0';
                        
                        args = extract_args(cmdStr, args);

                        /*for(i = 0; args[i] != NULL; i++)
                                printf("%s ", args[i]);*/
                        
                        forking_executing(args);
                }
                else
                {
                        perror("Error reading input.");
                        free(cmdStr);
                }

                if (write(1, "\n", 1) == -1)
                        perror("Error writing output.");
        }

        return 0;
}