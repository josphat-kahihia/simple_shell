#include "myShell.h"

void wait_child(pid_t child_id, char **usrInput)
{
        pid_t killChild;
        int status;

        killChild = waitpid(child_id, &status, 0);

        if (killChild == -1)
        {
                perror("waitpid");
                exit(EXIT_FAILURE);
                free(usrInput);
        }
}