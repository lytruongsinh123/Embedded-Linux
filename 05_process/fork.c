#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    pid_t child_pid;
    int counter = 2;
    printf("Gia tri khoi tao cua counter: %d\n", counter);
    child_pid = fork();
    if(child_pid >= 0)
    {
        if(child_pid == 0) /*Process child*/
        {
            printf("\nIm the child process, counter: %d\n", ++counter);
            printf("\nMy PID is: %d, my parent PID is: %d\n", getpid(), getppid());
        }
        else /*Process parent*/
        {
            printf("\nIm the parent process, counter: %d\n", ++counter);
            printf("\nMy PID is: %d\n", getpid());
        }
    }
    else
    {
        printf("fork() unsuccessfully\n");
    }
    return 0;
}