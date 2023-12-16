#ifndef SHELL
#define SHELL

/*Standard libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stddef.h>
#include <dirent.h>

/*#defines*/
#define MAXSIZE 1024 /* maximum input line length */

/*Function Prototypes*/
int prompt();
int handle_execution(char **arg);
ssize_t get_line(char **linePointer, size_t *lineLength, FILE *stream);
char *str_tok(char *string, const char * delimiter);
void copy(char to[], char from[]);
void forking_executing(char **argInput);
char **extract_args(char *cmdStr, char **args);
int _strcmp(const char *s1, const char *s2);
char *_stringChr(char *s, char c);
void wait_child(pid_t child_id, char **usrInput);
char **extract_path(char *path_var, char **path);


/* memory_functions2.c */
int bfree(void **);

/* buildin.c */
/* int _builtIn(char **token, list_t *env, int num, char **command); list_t undefined */

char *_strcpy(char *dest, char *src);


int _getLength(char *str);

#endif