#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int main(int argc, char* argv[])
{
    printf("Hello hung");
    sleep(5);
    printf("kill curent process");
    kill(getpid(), SIGKILL);
    while(1)
    {
        printf("Hello");
        sleep(2);
    }
    return 0;
}