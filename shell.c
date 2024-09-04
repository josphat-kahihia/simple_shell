#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Function to handle command execution
void handle_command(char *command) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        execlp(command, command, (char *)NULL);
        
        // If execlp returns, there was an error
        perror("Command not found");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        wait(NULL);
    }
}

int main() {
    char buffer[BUFFER_SIZE];
    
    while (1) {
        // Display the prompt
        printf("#cisfun$ ");
        fflush(stdout);
        
        // Read input from the user
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            // Handle EOF (Ctrl+D)
            if (feof(stdin)) {
                printf("\n");
                break;
            }
            perror("Read failed");
            continue;
        }
        
        // Remove the newline character from the end of the input
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Check if the input is empty
        if (strlen(buffer) == 0) {
            continue;
        }
        
        // Handle the command
        handle_command(buffer);
    }
    
    return 0;
}

