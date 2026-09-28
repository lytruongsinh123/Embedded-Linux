#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *ThreadA(void *arg)
{
    pthread_mutex_lock(&mutex1);
    printf("Thread A: da lock mutex1\n");

    sleep(1);

    printf("Thread A: dang cho mutex2...\n");
    pthread_mutex_lock(&mutex2);

    printf("Thread A: da lock mutex2\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

void *ThreadB(void *arg)
{
    pthread_mutex_lock(&mutex2);
    printf("Thread B: da lock mutex2\n");

    sleep(1);

    printf("Thread B: dang cho mutex1...\n");
    pthread_mutex_lock(&mutex1);

    printf("Thread B: da lock mutex1\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main()
{
    pthread_t threadA, threadB;

    pthread_create(&threadA, NULL, ThreadA, NULL);
    pthread_create(&threadB, NULL, ThreadB, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    return 0;
}