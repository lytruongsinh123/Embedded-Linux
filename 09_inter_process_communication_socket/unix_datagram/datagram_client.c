#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdio.h>

#define BUF_SIZE 10
#define SOCK_PATH "./sock_dgram"

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr;
    int fd, optval;
    size_t msgLen;
    ssize_t numBytes;

    char resp[BUF_SIZE];
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(fd == -1)
    {
        return 1;
    }

    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);

    optval = 1;
    // setsockopt(
    // fd,             // socket cần cấu hình
    // SOL_SOCKET,     // option thuộc socket layer
    // SO_PASSCRED,    // yêu cầu kernel truyền credentials
    // &optval,        // giá trị bật/tắt
    // sizeof(optval)  // kích thước
    // );
    setsockopt(fd, SOL_SOCKET, SO_PASSCRED, &optval, sizeof(optval));

    msgLen = strlen(argv[1]);
    if(sendto(fd, argv[1], msgLen, 0, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un)) != msgLen)
    {
        return 1;
    }
    numBytes = recvfrom(fd, resp, BUF_SIZE, 0, NULL, NULL);
    if(numBytes == -1)
    {
        return 1;
    }
    else
    {
        printf("Response : %s\n", resp);
    }
    return 0;
}

// | Level          | Ý nghĩa                 | Các option thường gặp                       |
// | -------------- | ----------------------- | ------------------------------------------- |
// | `SOL_SOCKET`   | Option chung của socket | `SO_REUSEADDR`, `SO_RCVBUF`, `SO_KEEPALIVE` |
// | `IPPROTO_TCP`  | Option riêng của TCP    | `TCP_NODELAY`, `TCP_KEEPIDLE`               |
// | `IPPROTO_IP`   | Option của IPv4         | `IP_TTL`, `IP_TOS`, `IP_MULTICAST_TTL`      |
// | `IPPROTO_IPV6` | Option của IPv6         | `IPV6_V6ONLY`, `IPV6_UNICAST_HOPS`          |
// | `IPPROTO_UDP`  | Option liên quan UDP    | ít option phổ biến hơn                      |
// | `IPPROTO_RAW`  | Raw IP socket           | dùng khi làm việc trực tiếp với IP          |

// | Option          | Dùng để làm gì                                                  |
// | --------------- | --------------------------------------------------------------- |
// | `SO_REUSEADDR`  | Cho phép bind lại địa chỉ/port trong một số trường hợp          |
// | `SO_REUSEPORT`  | Cho phép nhiều socket cùng bind một địa chỉ/port theo điều kiện |
// | `SO_KEEPALIVE`  | Kiểm tra kết nối TCP còn sống hay không                         |
// | `SO_RCVBUF`     | Thiết lập kích thước buffer nhận                                |
// | `SO_SNDBUF`     | Thiết lập kích thước buffer gửi                                 |
// | `SO_RCVTIMEO`   | Timeout cho thao tác nhận                                       |
// | `SO_SNDTIMEO`   | Timeout cho thao tác gửi                                        |
// | `SO_BROADCAST`  | Cho phép gửi broadcast                                          |
// | `SO_OOBINLINE`  | Đưa TCP urgent/OOB data vào luồng dữ liệu bình thường           |
// | `SO_LINGER`     | Quy định cách `close()` xử lý dữ liệu chưa gửi                  |
// | `SO_ERROR`      | Lấy lỗi gần nhất của socket                                     |
// | `SO_TYPE`       | Lấy loại socket                                                 |
// | `SO_ACCEPTCONN` | Kiểm tra socket có đang ở trạng thái `listen()` hay không       |
// | `SO_PASSCRED`   | Nhận PID/UID/GID của process gửi qua Unix Domain Socket         |
// | `SO_PEERCRED`   | Lấy credentials của peer trên Unix Domain Socket                |

