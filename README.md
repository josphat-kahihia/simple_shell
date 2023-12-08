simple_shell
Authors: 1.Josphat Kahihia  2.Clinton Nyakoe

HEADER FILE #ifndef SHELL_H #define SHELL_H #include <sys/wait.h>

#include <stdio.h> #include <stdlib.h> #include <string.h> #include <unistd.h> #include <sys/stat.h> #include <errno.h>

extern char **environ; int main(void); void execute(char **argv); char *which(char *cmd); size_t get_l(char **line, size_t *len, FILE *stream); char *get_input(const char *prompt); void free_tkn(char **tokens); char **tokenizer(const char *input, const char *delimiters); void exec_cmd(char **tokens);

#endif

SHELL UNDERSTANDING a shell is a program that provides a command-line interface (CLI) for interacting with an operating system (OS) or its services. our program is an emulation of the BASH SHELL with a simple implementattion.

Main Function

it is the starting point for program execution.
Execve Function -it executes a program in the current process. It replaces the current process's memory space with a new program, effectively loading and running the specified executable file.

Get_1 Function(custom getline function)

it accept a string from the input stream as an input.it reads a full line from a stream. It reads and stores the newline character as part of the string.
Free_tkn Function

It frees the memory allocated for the tokens array, which is a dynamically allocated array of strings. It iterates through the array, freeing the memory for each string element and then frees the memory for the array itself.
Tokenizer Function

It parses user input into individual tokens based on specified delimeters. It takes a user input string and a set of delimeters as input and returns a pointer to an array of parsed tokens.
Exec_cmd Function

executes parsed commands. It takes a pointer to an array of parsed tokens as input and executes the command specified by the tokens.
Get_input Function

It collects user input using a custom getline function. It takes a prompt as input which is displayed to the user before requesting input.
Which Function

It locates the path to a command specified by the user. It takes a command as input and returns a path to the command if it is found within the directories specified in the 'PATH' environment variable.
COMPILATION gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
