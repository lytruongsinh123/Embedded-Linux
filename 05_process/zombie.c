#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void func(int signum)
{
    printf("I'm in func() \n");
    wait(NULL);
}
int main(int argc, char* argv[])
{
    pid_t child_pid;
    child_pid = fork();
    if(child_pid >= 0)
    {
        if(child_pid == 0)
        {
            printf("\nI'm the child process, My pid is: %d\n", getpid());
            while(1);
        }
        else
        {
            signal(SIGCHLD, func);
            printf("\nIm the parent process");
            while(1);
        }
    }
    else
    {
        printf("fork() unsuccessfull\n");
    }
    return 0;
}