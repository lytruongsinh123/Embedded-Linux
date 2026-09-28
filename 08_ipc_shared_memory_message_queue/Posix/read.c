#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

#define SHARED_MEM_SIZE 100
#define FILE_NAME "hung_nmap"

int main()
{
    // Tạo share memory object
    int fd = shm_open(FILE_NAME, O_RDWR, 0666);
    if(fd < 0)
    {
        printf(" shm_open() is failed, %s. \n", strerror(errno));
        return -1;
    }
    // Set kích thước cho share memory object
    ftruncate(fd, SHARED_MEM_SIZE);
    // Map và Unmap share memory object
    char *data = (char*)mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    printf("%s: Read data: %s\n", __FILE__, data);

    // Unmap share memory object
    munmap(data, SHARED_MEM_SIZE);
    close(fd);
    return 0;
}
/*
 * void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 *
 * @brief Configure the size of the shared memory object.
 *
 * @param[in] addr
 *      Địa chỉ memory của calling process được map.
 *      Tương tự như shm nên set giá trị là 0 và kernel sẽ allocation
 *      địa chỉ phù hợp.
 *
 * @param[in] length
 *      Độ dài của shared memory object được map.
 *
 * @param[in] prot
 *      Memory protection của mapping (không được conflict với file permission).
 *      Có thể có các giá trị sau:
 *
 *      PROT_EXEC   --> Pages may be executed.
 *      PROT_READ   --> Pages may be read.
 *      PROT_WRITE  --> Pages may be written.
 *      PROT_NONE   --> Pages may not be accessed.
 *
 * @param[in] flags
 *      Các flag cho phép xác định cách vùng memory mapping được chia sẻ
 *      giữa các process.
 *
 *      MAP_SHARED ( Hai process riêng biệt )
 *          --> Các cập nhật của process này vào shared memory sẽ
 *              available với các process khác.
 *
 *      MAP_PRIVATE ( Mối quan hệ cha con )
 *          --> Sử dụng cơ chế copy-on-write.
 *              Khi process muốn ghi vào vùng nhớ, hệ điều hành sẽ tạo
 *              một bản copy riêng cho process đó.
 *              Các thay đổi này sẽ không visible đối với các process khác.
 *
 *      Ngoài ra, có thể kết hợp với một số flag khác bằng phép OR:
 *
 *      MAP_ANONYMOUS
 *          --> Tạo anonymous mapping.
 *              Toàn bộ vùng nhớ trên vùng này được khởi tạo là 0.
 *              Không cần quan tâm tới fd.
 *
 *      MAP_UNINITIALIZED
 *          --> Không khởi tạo vùng anonymous mapping.
 *
 * @param[in] fd
 *      Shared memory file descriptor.
 *
 * @param[in] offset
 *      Offset của shared memory object sẽ được mapping vào
 *      virtual memory của process.
 */