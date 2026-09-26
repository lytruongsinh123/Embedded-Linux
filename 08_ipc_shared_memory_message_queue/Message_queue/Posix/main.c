#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>

#define MQ_MODE (S_IRUSR | SIWUSR)
int main()
{
    struct mq_attr attrp;
    printf("Create mqueue\n");
    mqd_t mqid = mq_open("/mqueue", O_RDWR | O_CREAT | O_NONBLOCK, MQ_MODE, NULL);
    if(mqid == -1)
    {
        printf("mq_open() error %d: %s\n", errno, strerror(errno));
        return -2;
    }
    if(mq_getattr(mqid, &attrp) != 0)
    {
        printf("mq_open() error %d: %s\n", errno, strerror(errno));
        return -3;
    }
    if(attrp.mp_flags == 0)
    {
        printf("mp_flags = 0\n");
    }
    else
    {
        printf("mp_flags = O_NONBLOCK\n");
    }
    printf("mq_maxmsg = %ld\n", attrp.mq_maxmsg);
    printf("mq_msgsize = %ld\n", attrp.msgsize);
    printf("mq_curmsgs = %ld\n", attrp.mq_curmsgs);
}