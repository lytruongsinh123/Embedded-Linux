#include <sys/stat.h>   // Các kiểu dữ liệu/hằng số liên quan đến file permission
#include <stdio.h>      // printf(), sprintf()
#include <sys/file.h>   // flock(), LOCK_SH, LOCK_EX, LOCK_UN
#include <unistd.h>     // sleep(), close(), write()
#include <fcntl.h>      // open(), O_RDWR, O_CREAT

int main(void)
{
    int fd;
    char buf[16] = {0};

    if ((fd = open("./text.txt", O_RDWR)) == -1)
    {
        printf("can not open file \n");
        return 0;
    }
    else
    {
        printf("open file text.txt \n");
    }

    if (flock(fd, LOCK_EX | LOCK_NB) == -1)
    {
        printf("can not get write lock\n");
    }

    if (flock(fd, LOCK_SH | LOCK_NB) == -1)
    {
        printf("can not get read lock\n");
    }
    else
    {
        printf("get read lock file\n");

        if (read(fd, buf, sizeof(buf) - 1) == -1)
        {
            printf("can not read file \n");
            return 0;
        }
        else
            printf("%s\n", buf);
    }

    close(fd);
    return 0;
}