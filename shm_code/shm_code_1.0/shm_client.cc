#include "shm_h.hpp"

int main()
{
    // 获取key_t
    key_t key = ftok("./", 100);
    printf("key:%x\n", key);
    // 创建共享内存
    int shmid = shmget(key, 4096, 0);
    if (shmid == -1)
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(2);
    }
    printf("shmid:%d\n", shmid);

    
    void *addr = shmat(shmid, nullptr, 0); // 返回起始地址当数组处理,
    if ((long long)addr == -1l)            // linux指针是八个字节
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(2);
    }
    char* start = (char*)addr;

    // 通信
    int coun = 1;
    while (coun < 10 )
    {
        // 要求把我的pid,消息,次数都带过去
        char message[] = "你好我是客户端,现在给你发消息";
        snprintf(start,4096,"%s pid:%d 第[%d]次", message, getpid(), coun++);
        sleep(1);
    }

    sleep(10);
    // 4.取消挂接共享内存(不可以直接暴力删除,先去挂接)
    int deaddr = shmdt(start);
    if (deaddr == -1)
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(3);
    }

    return 0;
}