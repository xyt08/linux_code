#include "shm.h"

int main()
{
    //1.获取key
    key_t k = getkey();
    printf("client:k = %x\n",k);

    //2.获取共享内存
    int shmid = get_shm(k);
    printf("client_shmid:%d\n",shmid);

    //3.挂接
    char* addr = (char*)attachshmat(shmid);
    printf("挂接成功\n");

    char buff[64];
    int i = 1;
    char* message = "你好我是客户端";
    //4.通信
    while (1)
    {
        // //不要buff缓冲区
        // snprintf(buff, sizeof(buff), "%s %d 第%d次发","你好我是客户端",getpid(), i++);
        // memcpy(addr, buff, strlen(buff)+1);
        // sleep(1);

        //直接写到addr里面
        snprintf(addr, MAX_SIZE, "%s pid : %d 第%d次", message, getpid(), i++);
        sleep(1);
    }

	sleep(7);
    //5.去挂接
    detashmdt(addr);
    printf("去关联成功\n");
    return 0;
}
