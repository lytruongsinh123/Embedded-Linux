#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_SIZE 16
char *msg1 = "Hello hung1";
char *msg2 = "Hello hung2";
char *msg3 = "Hello hung3";

static void func(int signum)
{
    wait(NULL);
    printf("Child process termination\n");
}

int main(int argc, char const *argv[])
{
    char in_buff[MSG_SIZE];
    int num_read = 0;
    int fds[2];
    pid_t child_pid;
    if(pipe(fds) < 0)
    {
        printf("pipe() unsucessfully\n");
        exit(1);
    }
    child_pid = fork();
    if(child_pid >= 0)
    {
        if(child_pid == 0)
        {
            printf("I am Child\n"); // Reader
            while(1)
            {
                printf("Before Wait...\n");
                num_read = read(fds[0], in_buff, MSG_SIZE);
                printf("Finish Wait\n");
                if(num_read == -1)
                {
                    printf("read() failed\n");
                    exit(0);
                }
                else if (num_read == 0)
                {
                    printf("pipe end-of-pipe\n");
                }
                else
                {
                    printf("msg: %s %d\n", in_buff, num_read);
                }
            }
        }
        else
        {
            // Prevent zombie process
            signal(SIGCHLD, func);
            printf("I am Parent\n"); // Writer
            // Write into pipe
            sleep(5);
            write(fds[1], msg1, MSG_SIZE);
            sleep(5);
            write(fds[1], msg2, MSG_SIZE);
            sleep(5);
            write(fds[1], msg3, MSG_SIZE);
            sleep(5);
            if(close(fds[1]) == -1) // Write will see end-of-pipe
            {
                printf("close(fds[1]) failed\n");
            }
            while(1);
        }
    }
    else
    {
        printf("fork() unsuccessfully\n");
    }
}