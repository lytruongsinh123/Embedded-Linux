#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define MSG_SIZE 20
char *msg1 = "Hello hung1";
char pipe_buff[MSG_SIZE];
int fds[2];

void sig_handler1(int num)
{
    printf("I'm signal handler1: %d\n", num);
    write(fds[1], msg1, MSG_SIZE);
}
int main(int argc, char const *argv[])
{
    if(signal(SIGINT, sig_handler1) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(fds) < 0)
    {
        printf("pipe() unsucessfully\n");
        exit(1);
    }
    read(fds[0], pipe_buff, MSG_SIZE);
    printf("msg[%d]: %s\n", 1, pipe_buff);
    return 0;
}