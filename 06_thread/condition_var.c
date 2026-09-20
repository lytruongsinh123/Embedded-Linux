#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THRESHOLD 5

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int counter;

typedef struct {
    char name[30];
    char msg[30];
} thread_args_t;

static void* handle_th(void* args)
{
    thread_args_t *thr = (thread_args_t*) args;

    pthread_mutex_lock(&lock);
    printf("hello %s !\n", thr->name);
    while(counter < THRESHOLD)
    {
        counter += 1;
        printf("Counter: %d\n", counter);
        sleep(1);
    }
    pthread_cond_signal(&cond);
    printf("thread handler, counter = %d\n", counter);
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int ret;
    thread_args_t thr;
    pthread_t thread_id;
    memset(&thr, 0x0, sizeof(thread_args_t));

    if(ret = pthread_create(&thread_id, NULL, &handle_th, &thr))
    {
        printf("thread_create() error number = %d\n", ret);
        return -1;
    }

    pthread_mutex_lock(&lock);
    while(1)
    {
        printf("check\n");
        pthread_cond_wait(&cond, &lock);
        printf("Check full\n");
        if(counter == THRESHOLD)
        {
            printf("Global variable counter = %d\n", counter);
            break;
        }
    }
    pthread_mutex_unlock(&lock);
    pthread_join(thread_id, NULL);
    return 0;
}
