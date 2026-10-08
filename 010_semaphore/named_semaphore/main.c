#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#define POSIX_SEM_NAMED      "/named_app1"
#define R_W_PERM             0666
#define SEM_WAITING_TIMEOUT  10000
#define MSECS_IN_SEC         1000

int main(int argc, char* argv[])
{
    char c;
    int ret = -1;
    int current_value;

    sem_t* sem;
    struct timespec timeout;

    sem = sem_open(POSIX_SEM_NAMED, O_CREAT | O_EXCL, R_W_PERM, 1);
    if(sem == SEM_FAILED)
    {
        /* Nếu lỗi semaphore thật */
        if(errno != EEXIST)
        {
            printf("Failed to open semaphore error: %s\n", strerror(errno));
            return -1;
        }
        /* Nếu lỗi là so semaphore đã tồn tại */
        printf("%s, Reading available semaphore.\n", argv[0]);

        /* Mở semaphore đã tồn tại */
        sem = sem_open(POSIX_SEM_NAMED, 0);

        /* Nếu lỗi mở semaphore tiếp */
        if(sem == SEM_FAILED)
        {
            printf("Failed to open semaphore error: %s\n", strerror(errno));
            return -1;
        }
    }

    /* Get current semaphore */
    sem_getvalue(sem, &current_value);
    printf("Current semaphore value = %s.\n", current_value);

    /* Locking with timeout */
    /*
    * Lấy thời gian hiện tại của hệ thống.
    * CLOCK_REALTIME: lấy thời gian thực hiện tại.
    * Kết quả được lưu vào biến timeout.
    */
    if (clock_gettime(CLOCK_REALTIME, &timeout) == -1)
    {
        printf("Không thể lấy thời gian hiện tại: %s\n", strerror(errno));
        return -1;
    }

    /*
    * Cộng thêm thời gian chờ vào thời gian hiện tại.
    *
    * timeout.tv_sec: phần thời gian tính theo giây.
    *
    * Sau câu lệnh này:
    *     timeout = thời gian hiện tại + thời gian chờ
    *
    * Đây sẽ là thời điểm tối đa mà sem_timedwait()
    * được phép chờ semaphore.
    */
    timeout.tv_sec += SEM_WAITING_TIMEOUT / MSECS_IN_SECL;

    /*
    * Chờ semaphore với thời gian giới hạn.
    *
    * Nếu semaphore đang có sẵn:
    *     -> lấy semaphore ngay và trừ đi 1.
    *
    * Nếu semaphore đang bị giữ:
    *     -> tiến trình sẽ phải chờ.
    *
    * Tiến trình sẽ tiếp tục khi:
    *     1. Một tiến trình khác gọi sem_post()
    *     2. Thời gian chờ bị hết.
    */
    ret = sem_timedwait(sem, &timeout);

    if (ret == -1)
    {
        /*
        * Không lấy được semaphore.
        *
        * errno có thể cho biết nguyên nhân:
        *
        * ETIMEDOUT: thời gian chờ đã hết.
        * EINTR:     tiến trình bị gián đoạn bởi signal.
        */
        printf("Không thể chờ semaphore: %s\n", strerror(errno));
        return -1;
    }
    /* Get current semaphore */
    sem_getvalue(sem, &current_value);
    printf("Current semaphore value = %s.\n", current_value);

    /* Get any character to go next */
    printf("%s, Please type any character: ", argv[0]);
    c = getchar();

    /* Tăng semaphore lên 1 đơn vị */
    ret = sem_post(sem);
    if (ret == -1)
    {
        printf("Failed to release semaphore error: %s\n", strerror(errno));
        return -1;
    }
    /* Get current semaphore */
    sem_getvalue(sem, &current_value);
    printf("Current semaphore value = %d.\n", current_value);

    ret = sem_close(sem);
    if (ret == -1)
    {
        printf("%s, Failed to close semaphore error: %s\n",
            argv[0], strerror(errno));
        return -1;
    }

    sem_unlink(&sem);
}