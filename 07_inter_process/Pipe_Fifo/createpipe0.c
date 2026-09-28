#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define MSG_SIZE 20
char *msg1 = "Hello hung1";
char *msg2 = "Hello hung2";
char *msg3 = "Hello hung3";
char *msg4 = "Hello hung4";

char pipe_buff[MSG_SIZE];
int fds[2];

int main(int argc, char const *argv[])
{
    if(pipe(fds) < 0)
    {
        printf("pipe() unsuccessfully\n");
        exit(1);
    }
    write(fds[1], msg1, MSG_SIZE);
    write(fds[1], msg2, MSG_SIZE);
    write(fds[1], msg3, MSG_SIZE);
    printf("Sleep 2 seconds\n");
    sleep(2);
    for(int i = 0; i < 3; i++)
    {
        read(fds[0], pipe_buff, MSG_SIZE);
        printf("msg[%d]: %s\n", i+1, pipe_buff);
    }
    return 0;
}