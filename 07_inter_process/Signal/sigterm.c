#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
void sig_handler1(int num)
{
    printf("\nI'm signal handler1: %d\n", num);
    exit(EXIT_SUCCESS);
}
void sig_handler2(int num)
{
    printf("I'm signal handler2: %d\n", num);
}
void sig_handler3(int num)
{
    printf("I'm signal handler3: %d\n", num);
    exit(EXIT_SUCCESS);
}
int main()
{
    
    signal(SIGTERM, sig_handler3); // có thể catch được nên khi gọi kill -SIGTERM <pid> nó sẽ vào handler3
    printf("Process ID: %d\n", getpid());
    while(1)
    {
        printf("Hello hungbro\n");
        sleep(2);
    }
}