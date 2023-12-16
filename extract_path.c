#include "myShell.h"

/**
 * extract_path - creates an argument vector
 * 
 * Return: Path Vector (char **path)
 */
char **extract_path(char *path_var, char **path)
{
        char *token = NULL;
        char *pathCpy = NULL;
        int token_count = 0;
        int token_len = 0;
        int i;

        /**
         * Run strtok, Malloc char **path from the number of path
         * Malloc the individual argument strings from their length
         * 
         * Copy the string tokens to the argument string
         * 
         * Return path;
         */

        pathCpy = malloc(sizeof(char) * (MAXSIZE * 2));

        strcpy(pathCpy, path_var);
                token = strtok(pathCpy, " ");

        while (token != NULL)
        {
                token_count++;
                token = strtok(NULL, " ");
        }
        path = malloc(sizeof(char) * token_count);
        
        token = strtok(path_var, "=");
        for (i = 0; token!=NULL; i++)
        {
                token = strtok(NULL, ":");
                token_len = strlen(token);
                path[i] = malloc(sizeof(char) * token_len); /*Strlen is another utility */
                strcpy(path[i], token);
        }
        path[i] = NULL;

        return path;
}