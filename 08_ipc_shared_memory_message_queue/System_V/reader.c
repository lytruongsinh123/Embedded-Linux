#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 0x1234

int main()
{

    // Tạo key chung Identifier
    key_t key = ftok("./shmfile", 65);
    // Truy cập id share memory
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    // shmaddr tự động phân vào vùng nhớ share memory
    char *shmaddr = (char*)shmat(shmid, (void*)0, 0);
    // đọc
    printf("Data read from memory: %s\n", shmaddr);
    // gỡ shmaddr khỏi vùng nhớ
    shmdt(shmaddr);
    // giải phỏng share memory
    shmctl(shmid, IPC_RMID, NULL);
}