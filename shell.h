#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args);
void execute_script(char *filename);

#endif

