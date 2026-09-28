#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

typedef struct
{
    char hoten[100];
    char ngaysinh[20];
    char quequan[100];
} SinhVien_t;


/* =========================
 * MUTEX + CONDITION
 * ========================= */

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_input = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_write = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_read  = PTHREAD_COND_INITIALIZER;


/* =========================
 * TRẠNG THÁI
 * ========================= */

/*
 * read_done = 1:
 *     T3 đã đọc xong -> T1 được phép nhập
 *
 * input_done = 1:
 *     T1 nhập xong -> T2 được phép ghi
 *
 * write_done = 1:
 *     T2 ghi xong -> T3 được phép đọc
 */

int read_done  = 1;
int input_done = 0;
int write_done = 0;

SinhVien_t sv;


/* =====================================================
 * THREAD 1: NHẬP SINH VIÊN
 * ===================================================== */

void *thread1_func(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);

        /*
         * Nếu T3 chưa đọc xong thì T1 phải ngủ và nhả lock cho thread khác sử dụng
         */
        while (read_done == 0)
        {
            pthread_cond_wait(&cond_input, &lock);
        }

        /*
         * Đánh dấu rằng T1 bắt đầu nhập dữ liệu mới.
         */
        read_done = 0;

        printf("\n===== NHAP SINH VIEN =====\n");

        printf("Ho ten: ");
        fgets(sv.hoten, sizeof(sv.hoten), stdin);
        sv.hoten[strcspn(sv.hoten, "\n")] = '\0';

        printf("Ngay sinh: ");
        fgets(sv.ngaysinh, sizeof(sv.ngaysinh), stdin);
        sv.ngaysinh[strcspn(sv.ngaysinh, "\n")] = '\0';

        printf("Que quan: ");
        fgets(sv.quequan, sizeof(sv.quequan), stdin);
        sv.quequan[strcspn(sv.quequan, "\n")] = '\0';

        /*
         * T1 nhập xong.
         * Báo cho T2 biết có dữ liệu để ghi.
         */
        input_done = 1;

        pthread_cond_signal(&cond_write);

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}


/* =====================================================
 * THREAD 2: GHI FILE
 * ===================================================== */

void *thread2_func(void *arg)
{
    int fd;
    char text[300];

    while (1)
    {
        pthread_mutex_lock(&lock);

        /*
         * Nếu T1 chưa nhập xong thì T2 phải ngủ và nhả lock cho thread khác sử dụng
         */
        while (input_done == 0)
        {
            pthread_cond_wait(&cond_write, &lock);
        }

        printf("\n[T2] Nhan duoc du lieu tu T1\n");

        /*
         * Mở file.
         *
         * O_WRONLY : chỉ ghi
         * O_CREAT  : nếu chưa có thì tạo
         * O_APPEND : ghi thêm vào cuối file
         */
        fd = open("./thongtinsinhvien.txt",
                  O_WRONLY | O_CREAT | O_APPEND,
                  0666);

        if (fd == -1)
        {
            perror("open");
            pthread_mutex_unlock(&lock);
            return NULL;
        }

        snprintf(text,
                 sizeof(text),
                 "%s | %s | %s\n",
                 sv.hoten,
                 sv.ngaysinh,
                 sv.quequan);

        if (write(fd, text, strlen(text)) == -1)
        {
            perror("write");
            close(fd);
            pthread_mutex_unlock(&lock);
            return NULL;
        }

        printf("[T2] Write file successfully\n");

        close(fd);

        /*
         * T2 đã ghi xong.
         */
        input_done = 0;
        write_done = 1;

        /*
         * Báo cho T3 biết T2 đã ghi xong.
         */
        pthread_cond_signal(&cond_read);

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}


/* =====================================================
 * THREAD 3: ĐỌC FILE
 * ===================================================== */

void *thread3_func(void *arg)
{
    int fd;
    char buf[300];
    ssize_t bytes_read;

    while (1)
    {
        pthread_mutex_lock(&lock);

        /*
         * Nếu T2 chưa ghi xong thì T3 phải ngủ và nhả lock cho thread khác sử dụng
         */
        while (write_done == 0)
        {
            pthread_cond_wait(&cond_read, &lock);
        }

        printf("\n[T3] Nhan duoc tin hieu read\n");

        /*
         * Mở file chỉ để đọc.
         */
        fd = open("./thongtinsinhvien.txt", O_RDONLY);

        if (fd == -1)
        {
            perror("open");
            pthread_mutex_unlock(&lock);
            return NULL;
        }

        /*
         * Đọc dữ liệu từ file.
         */
        bytes_read = read(fd, buf, sizeof(buf) - 1);

        if (bytes_read < 0)
        {
            perror("read");
            close(fd);
            pthread_mutex_unlock(&lock);
            return NULL;
        }

        /*
         * read() không tự thêm '\0'.
         */
        buf[bytes_read] = '\0';

        printf("[T3] Doc du lieu:\n");
        printf("%s", buf);

        close(fd);

        /*
         * T3 đã đọc xong.
         */
        write_done = 0;
        read_done = 1;

        /*
         * Báo cho T1 biết T3 đã đọc xong.
         */
        pthread_cond_signal(&cond_input);

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}


/* =====================================================
 * MAIN
 * ===================================================== */

int main(void)
{
    int ret;

    pthread_t thread_id1;
    pthread_t thread_id2;
    pthread_t thread_id3;


    /* Tạo Thread 1 */
    ret = pthread_create(&thread_id1,
                         NULL,
                         thread1_func,
                         NULL);

    if (ret != 0)
    {
        printf("pthread_create T1 error = %d\n", ret);
        return -1;
    }


    /* Tạo Thread 2 */
    ret = pthread_create(&thread_id2,
                         NULL,
                         thread2_func,
                         NULL);

    if (ret != 0)
    {
        printf("pthread_create T2 error = %d\n", ret);
        return -1;
    }


    /* Tạo Thread 3 */
    ret = pthread_create(&thread_id3,
                         NULL,
                         thread3_func,
                         NULL);

    if (ret != 0)
    {
        printf("pthread_create T3 error = %d\n", ret);
        return -1;
    }


    /*
     * Các thread chạy vô hạn,
     * nên join sẽ chờ vô hạn.
     */
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);


    return 0;
}