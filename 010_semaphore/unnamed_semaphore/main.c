#include <stdlib.h>
#include <sys/mman.h>    // mmap()
#include <stdio.h>       // IO stuff
#include <unistd.h>      // sleep()
#include <semaphore.h>   // semaphore()
#include <time.h>        // time()

#define BUFFER_SIZE 10

typedef struct Buffer
{
    char **Tuples;
    int inSlotIndex;
    int outSlotIndex;
} Buffer;

int main()
{
    /* Create shared memory */
    int *buffer = (char *)mmap(NULL, sizeof(int)* BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    /* Create shared semaphores */
    sem_t *mutex = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *full  = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *empty = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(mutex, 1, 1);
    sem_init(full , 1, 0);           /* 0 đĩa nào có thức ăn    */
    sem_init(empty, 1, BUFFER_SIZE); /* 10 đĩa thức ăn đều rỗng */
    
    /* Forking */
    pid_t producer;
    pid_t consumer;

    /* Child producer process */
    if((producer = fork()) == 0)
    {
        while(1)
        {
            sem_wait(empty); /* empty = 10 - 1 = 9 lấy 1 đĩa ra làm thức ăn, còn 9 đĩa rỗng*/
            sem_wait(mutex); /* mutex =  1 - 1 = 0 đang làm đồ ăn nhân viên chưa được đưa ra bàn ăn */
            printf("Producer creates something\n");

            sem_post(full); /* full = 0 + 1 = 1 làm xong 1 đĩa có thức ăn */
            sem_post(mutex);/* mutex = 0 + 1 = 1 hoàn thành xong nhân viên được đưa ra bàn ăn */

            /* Sleep between 0 and 5 seconds */
            srand(time(NULL));
            sleep(rand() % 5);
        }
    }
    /* Child consumer process */
    if((consumer = fork()) == 0)
    {
        while(1)
        {
            sem_wait(full); /* full = 1 - 1 = 0  khách hàng đợi đĩa ăn nếu đĩa thức ăn vừa làm được nhân viên đưa ra lên hiện tại lại 0 có đĩa nào có thức ăn*/
            sem_wait(mutex);/* mutex = 1 - 1 = 0 khách nhận được thức ăn từ nhân viên */

            printf("Consumer takes something\n");

            sem_post(mutex);/* mutex = 0 + 1 = 1 báo hiệu đầu bếp tiếp tục làm thức ăn mới */
            sem_post(empty);/* empty = 9 + 1 = 10*/

            /* Sleep between 5 and 8 seconds */
            srand(time(NULL));
            sleep(3 + rand() % 5);
        }
    }
    /* Parent */
    else
    {
        while(1)
        {
            sleep(10);
            int takenSlots;
            sem_getvalue(full, &takenSlots);
            printf("Items in the buffer: %d/%d\n", takenSlots, BUFFER_SIZE);
        }
    }
}