#include "myShell.h"

void forking_executing(char **args)
{
        pid_t child;
        pid_t my_shell_pid;
        extern char **environ;
        char *path_var = NULL;
        char **path = NULL;
        int i;
        int j;

        for (int i = 0; environ[i] != NULL; i++)
        {
                for (int j = 0; environ[i][j] != '\0'; j++)
                {
                if (environ[i][j] == 'P' && environ[i][j + 1] == 'A' && environ[i][j + 2] == 'T' && environ[i][j + 3] == 'H') 
                {
                     path_var = environ[i];
                }
                }
        }

        if (path_var != NULL)
                path = extract_path(path_var, path);
        else
                if (write(2, "Error extracting path\n", 23) == -1)
                        perror("Error Writing to stderr");


        if (_stringChr(args[0], '/') != NULL)
        {
                child = fork();
                if (child == -1)
                {
                        perror("fork");
                        exit(EXIT_FAILURE);
                }

                if (child == 0)
                {
                        if (execve(args[0], args, environ) == -1)
                        {
                                perror("No such file or directory");
                                exit(EXIT_FAILURE);
                        }
                        free(args);
                }
                else
                {
                        wait_child(child, args);
                }
        }
        else
        {
                /**
                 * This segment should first read the contents of the directory
                 * specified by the PATH environment variable
                 */
                for (i = 0, j = 0; args[i] != NULL; i++)
                {
                        const char *directory_path = path[i];
                        const char *target_binary = args[0];

                        DIR *dir = opendir(directory_path);

                        if (dir == NULL) {
                                perror("Error opening directory");
                                exit(EXIT_FAILURE);
                        }

                        struct dirent *entry;

                        /*Read each entry in the directory */
                        while ((entry = readdir(dir)) != NULL) 
                        {
                                /* Check if the entry is a regular file*/
                                if (entry->d_type == DT_REG)
                                {
                                        /*Compare the entry name with the target binary name*/
                                        if (_strcmp(entry->d_name, target_binary) == 0)
                                        {
                                                printf("Found binary: %s\n", entry->d_name);
                                                if (directory_path = realloc(directory_path, (sizeof(directory_path) + sizeof(entry->d_name))) != NULL)
                                                {
                                                        strcat(directory_path, entry->d_name);
                                                        if (args[0] = realloc(args[0], sizeof(directory_path)) != NULL);
                                                                args[0] = directory_path;
                                                }
                                                child = fork();
                                                if (child == -1)
                                                {
                                                        perror("fork");
                                                        exit(EXIT_FAILURE);
                                                }

                                                if (child == 0)
                                                {
                                                        if (execve(args[0], args, environ) == -1)
                                                        {
                                                                perror("Error on execve");
                                                                exit(EXIT_FAILURE);
                                                        }
                                                        free(args);
                                                }
                                                else
                                                {
                                                        wait_child(child, args);
                                                }

                                                break;  /* You can break out of the loop if you've found what you need*/
                                        }
                                }
                        }
                }
        }
}