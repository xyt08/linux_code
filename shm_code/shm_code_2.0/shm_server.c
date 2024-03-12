#include "shm.h"

int main()
{
    // 1.获取key
    key_t k = getkey();
    printf("server:k = %x\n", k);
    // 2.创建共享内存
    int shmid = create_shm(k);
    // // 3.挂接
    char *addr = attachshmat(shmid);
    printf("挂接成功\n");
    //4.通信
    while (1)
    {
        printf("client : %s\n", addr);
        sleep(1);
    }
    
    //去挂接
    detashmdt(addr);
    printf("去关联成功\n");

    sleep(5);
    // 6.释放内存
    deshmctl(shmid);
    printf("删除成功\n");

    return 0;
}
