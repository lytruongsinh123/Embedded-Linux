#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>

#define BUF_SIZE 10
#define SOCK_PATH "./sock_dgram"

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr, claddr;
    int fd, j;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];
    /* Tạo socket dựa trên file desciptor*/
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(fd == -1)
    {
        return 1;
    }
    memset(&svaddr, 0, sizeof(struct sockaddr_un));

    /* Set domain cho server */
    svaddr.sun_family = AF_UNIX;
    /* Set path cho server */
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);


    /* Bind socket vào server hay còn gọi là gán tài nguyên */
    if(bind(fd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un)) == -1)
    {
        return 1;
    }
    printf("Start listening on server \n");
    for(;;)
    {
        len = sizeof(struct sockaddr_un);

        /* Nhận dữ liệu từ client rồi gán vào buf */
        numBytes = recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &len);
        if(numBytes == -1)
        {
            return 1;
        }
        /* Sau khi nhận claddr sẽ được gán địa chỉ */


        printf("Server received %ld bytes from %s \n", (long) numBytes, claddr.sun_path);

        /* Viết hoa buffer vừa nhận được */
        for(j = 0; j < numBytes; j++)
        {
            buf[j] = toupper((unsigned char) buf[j]);
        }

        /* Gửi dữ liệu buffer đã viết hoa cho client */
        if(sendto(fd, buf, numBytes, 0, (struct sockaddr *)&claddr, len) != numBytes)
        {
            printf("Sendto error\n");
        }
    }
}