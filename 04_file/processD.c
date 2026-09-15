#include <sys/stat.h>   // Các kiểu dữ liệu/hằng số liên quan đến file permission
#include <stdio.h>      // printf(), sprintf()
#include <sys/file.h>   // flock(), LOCK_SH, LOCK_EX, LOCK_UN
#include <unistd.h>     // sleep(), close(), write()
#include <fcntl.h>      // open(), O_RDWR, O_CREAT

int main(void)
{
    int fd;
    char text[10] = {0};
    struct flock fl;

    sprintf(text, "Dotuanhung\n");

    if ((fd = open("./text.txt", O_RDWR)) == -1)
    {
        printf("can not open file \n");
        return 0;
    }
    else
    {
        printf("open file text.txt \n");
    }
    fl.l_start = 1; /*Offset where the lock begins*/
    fl.l_len = 5;   /*Number of bytes to lock; 0 means "until EOF"*/
    fl.l_type = F_WRLCK; /*Lock type: F_RDLCK, F_WRLCK, F_UNLCK*/
    fl.l_whence = SEEK_SET /*How to interpret 'l_start' : SEEK_SET, SEEK_CUR, SEEK_END*/
    if(fcnt(fd, F_SETLK, &fl) == -1)
    {
        printf("can not write lock byte 1-5\n");
    }
    
    fl.l_start = 6; /*Offset where the lock begins*/
    fl.l_len = 8;   /*Number of bytes to lock; 0 means "until EOF"*/
    fl.l_type = F_WRLCK; /*Lock type: F_RDLCK, F_WRLCK, F_UNLCK*/
    fl.l_whence = SEEK_SET /*How to interpret 'l_start' : SEEK_SET, SEEK_CUR, SEEK_END*/
    if(fcntl(fd, F_SETLK, &fl) == -1) {
        printf("can not set write lock byte 6-11\n");
    } 
    else 
    {
        printf("set write lock byte 6-11\n");
        lseek(fd, 6, SEEK_SET);

        if(write(fd, text, sizeof(text) - 1) == -1) 
        {
            printf("can not write file\n");
            return 0;
        } 
        else 
        {
            printf("write file\n");
        }
    }
    while(1) {
        sleep(1);
    }
    close(fd);
    return 0;
}