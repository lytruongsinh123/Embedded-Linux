#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[])
{
    pid_t child_pid;
    int status, rv;
    child_pid = fork();
    if(child_pid >= 0)
    {
        if(child_pid == 0)
        {
            printf("\nI'm the child process, My pid is: %d\n", getpid());
            // while(1);
            exit(10);
        }
        else
        {
            rv = wait(&status);
            if(rv == -1) printf("wait() unsuccessful \n");
            printf("\n I'm the parent process, Pid child process: %d\n", rv);
            if(WIFEXITED(status))
            {
                printf("Normally termination, status = %d\n", WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status))
            {
                printf("Killed by signel, value = %d\n", WTERMSIG(status));
            }
        }
    }
    else
    {
        printf("fork() unsuccessfull\n");
    }
    return 0;
}