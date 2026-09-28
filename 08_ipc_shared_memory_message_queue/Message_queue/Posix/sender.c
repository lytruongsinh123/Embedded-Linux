#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>

int main()
{
    mqd_t mq;
    char message[] = "Hello Hung";
    mq = mq_open(
        "/hung_queue",
        O_CREAT | O_WRONLY,
        0666,
        NULL
    );
    if (mq == (mqd_t)-1)
    {
        perror("mq_open");
        return 1;
    }
    mq_send(
        mq,
        message,
        strlen(message) + 1,
        10
    );
    printf("Message sent\n");
    mq_close(mq);
    return 0;
}