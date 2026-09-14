#include <sys/stat.h>   // Các kiểu dữ liệu/hằng số liên quan đến file permission
#include <stdio.h>      // printf(), sprintf()
#include <sys/file.h>   // flock(), LOCK_SH, LOCK_EX, LOCK_UN
#include <unistd.h>     // sleep(), close(), write()
#include <fcntl.h>      // open(), O_RDWR, O_CREAT

int main(void)
{
    int fd;             // fd = File Descriptor
                        // Đây là số nguyên đại diện cho file đang được mở

    char text[16] = {0};
                        // Tạo một mảng char có 16 byte
                        // Ban đầu toàn bộ phần tử được khởi tạo bằng 0 ('\0')

    sprintf(text, "hello world\n");
                        // Ghi chuỗi "hello world\n" vào mảng text
                        //
                        // "hello world\n" có:
                        // hello       = 5 byte
                        // khoảng trắng = 1 byte
                        // world       = 5 byte
                        // \n          = 1 byte
                        // ----------------
                        // Tổng         = 12 byte
                        //
                        // Sau đó sprintf() thêm '\0' ở cuối
                        // => text thực tế chứa 13 byte có ý nghĩa

    if ((fd = open("./text.txt", O_RDWR | O_CREAT, 0666)) == -1)
    {
        // open() mở file ./text.txt
        //
        // O_RDWR:
        //      Mở file để vừa đọc vừa ghi
        //
        // O_CREAT:
        //      Nếu text.txt chưa tồn tại thì tạo file mới
        //
        // 0666:
        //      Permission ban đầu khi tạo file
        //      rw-rw-rw-
        //
        //      Permission thực tế còn phụ thuộc vào umask
        //
        // open() trả về:
        //      >= 0  -> File Descriptor
        //      -1    -> lỗi
        //
        // fd được nhận giá trị FD mà kernel cấp cho process

        printf("Can not create file \n");
        return 0;
    }
    else
    {
        printf("Create file text.txt\n");
    }


    if (write(fd, text, sizeof(text) - 1) == -1)
    {
        // write() ghi dữ liệu vào file mà fd đang đại diện
        //
        // write(fd, text, sizeof(text) - 1)
        //
        // fd:
        //      File Descriptor của text.txt
        //
        // text:
        //      Buffer chứa dữ liệu cần ghi
        //
        // sizeof(text) - 1:
        //      sizeof(text) = 16
        //      => ghi 15 byte
        //
        // !!! Chú ý:
        // "hello world\n" chỉ cần 12 byte + '\0'
        // nhưng ở đây bạn yêu cầu write() ghi 15 byte.
        //
        // Vì text được khai báo:
        // char text[16] = {0};
        //
        // nên 3 byte sau '\0' cũng vẫn tồn tại trong mảng
        // và có giá trị 0.
        //
        // write() KHÔNG quan tâm '\0'.
        // Nó cứ ghi đúng số byte mà bạn yêu cầu.
        //
        // Giá trị trả về của write():
        //      > 0  -> số byte thực tế đã ghi
        //      -1   -> lỗi
        //
        // Ví dụ:
        //      write(...) = 15
        // nghĩa là kernel đã ghi 15 byte.

        printf("Cannot write file \n");
        return 0;
    }
    else
    {
        printf("Write file \n");
    }


    if (flock(fd, LOCK_SH) == -1)
    {
        // flock() thiết lập LOCK trên file mà fd đang trỏ tới
        //
        // fd:
        //      File Descriptor của text.txt
        //
        // LOCK_SH:
        //      Shared Lock
        //      = khóa chia sẻ / khóa đọc
        //
        // Nhiều process có thể cùng giữ LOCK_SH
        //
        // Nhưng process muốn LOCK_EX thì phải chờ
        // các LOCK_SH được giải phóng.
        //
        // flock() trả về:
        //      0  -> thành công
        //      -1 -> lỗi
        //
        // !!! flock() KHÔNG tạo FD mới.
        // Nó sử dụng FD "fd" đã có.

        printf("Cannot set read lock\n");
    }
    else
    {
        printf("Set read lock\n");
    }


    while (1)
    {
        // Vòng lặp vô hạn
        //
        // Process sẽ không kết thúc.
        //
        // Mục đích ở đây là giữ cho file vẫn đang được mở
        // và LOCK_SH vẫn còn tồn tại.

        sleep(1);
        // Cho process ngủ 1 giây
        //
        // Sau 1 giây lại quay lại while
        //
        // => process cứ tồn tại mãi
        // => fd vẫn mở
        // => LOCK_SH vẫn được giữ
    }


    close(fd);
    // Đóng File Descriptor
    //
    // Tuy nhiên dòng này KHÔNG BAO GIỜ được thực hiện
    // vì while(1) là vòng lặp vô hạn.
    //
    // Nếu process bị terminate/kill thì kernel sẽ đóng
    // các FD của process và lock tương ứng cũng được giải phóng.

    return 0;
}