#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const* argv[])
{
    // Tạo key chung
    key_t key = ftok("./shmfile", 65);

    // Tạo segment share memory
    // key 
    // 1024 : size of share memory
    // 0666 : shmflag quyền của người dùng đối với share memory
    // IPC_CREAT : flag tạo share memory
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Attach share memory, str tự động được phân tới 1 vùng trong share memory
    // void *shmat(int shmid, const void *shmaddr, int shmflg
    // shmid : share memory id
    // (void *) : Nếu là 0 kernel tự động attach một vùng nhớ
    // SHM_RDONLY (0) : 
    char *str = (char*)shmat(shmid, (void *)0, 0);
    printf("Message to shared memory: ");
    fgets(str, 1024, stdin);
    while(1);
    // Detach share memory
    shmdt(str);

}