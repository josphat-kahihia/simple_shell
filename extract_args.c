#include "myShell.h"
/**
 * extract_args - creaters an argument vector
 * 
 * Return: An argument vector (char **arg)
 */
char **extract_args(char *cmdStr, char **args)
{
        char *token = NULL;
        char *cmdStrCpy = NULL;
        int token_count = 0;
        int token_len = 0;
        int i;

        /**
         * Run strtok, Malloc char **args from the number of args
         * Malloc the individual argument strings from their length
         * 
         * Copy the string tokens to the argument string
         * 
         * Return args;
         */

        cmdStrCpy = malloc(sizeof(char) * MAXSIZE);

        strcpy(cmdStrCpy, cmdStr);
                token = strtok(cmdStrCpy, " ");

        while (token != NULL)
        {
                token_count++;
                token = strtok(NULL, " ");
        }
        token_count++; /*holds the last token:'\0'*/
        args = malloc(sizeof(char) * token_count);
        
        token = strtok(cmdStr, " ");
        for (i = 0; token!=NULL; i++)
        {
                token_len = strlen(token);
                args[i] = malloc(sizeof(char) * token_len); /*Strlen is another utility */
                strcpy(args[i], token);

                token = strtok(NULL, " ");
        }
        args[i] = NULL;

        return args;
}