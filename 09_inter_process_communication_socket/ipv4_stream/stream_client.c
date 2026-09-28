#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG 5
#define BUFF_SIZE 256
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)


/* Chức năng chat */
void chat_func(int server_fd)
{
    int numb_read, numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];

    while(1)
    {
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);
        
        /* Ghi dữ liệu tới server thông qua hàm wrtie */
        printf("Please enter the message : ");
        fgets(sendbuff, BUFF_SIZE, stdin);
        numb_write = write(server_fd, sendbuff, sizeof(sendbuff));
        if (numb_write == -1)
        {
            handle_error("write()");
        }
        if(strncmp("exit", sendbuff, 4) == 0)
        {
            system("clear");
            break;
        }


        /* Nhận phản hồi trừ server bằng hàm read */
        numb_read = read(server_fd, recvbuff, sizeof(recvbuff));
        if(numb_read < 0)
        {
            handle_error("read()");
        }
        if(strncmp("exit", recvbuff, 4) == 0)
        {
            printf("Server exit ... \n");
            break;
        }
        printf("\n Message from Server: %s\n", recvbuff);
    }
    close(server_fd);
}
int main(int argc, char *argv[])
{
    int port_no;
    int server_fd;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    /* Đọc port number trên command line */
    if(argc < 3)
    {
        printf("command: ./client <server address> <port number>\n");
        exit(1);
    }
    port_no = atoi(argv[2]);

    /* Khởi tạo địa chỉ cho server */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);

    /* Chuyển đối chuỗi về dạng địa chỉ và lưu vào trong biến serv_addr.sin_addr */
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1)
    {
        handle_error("inet_pton()");
    }

    /* Tạo socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1)
    {
        handle_error("socket()");
    }

    /* kết nối server */
    if(connect(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        handle_error("connect()");
    }

    chat_func(server_fd);
    return 0;
}