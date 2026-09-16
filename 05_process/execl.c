#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("Before execl \n");
    execl("fork", "Dotuanhung", NULL);
    printf("After execl");
    return 0;
}