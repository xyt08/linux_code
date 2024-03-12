#include "shm_h.hpp"

//共享内存
int main()
{
    //1.创建共享内存
    //1.1先获取key
    key_t key = ftok("./", 100);
    printf("key:%x\n", key);
    //1.2创建
    int shmid = shmget(key, 4096, IPC_CREAT | IPC_EXCL | 0660);
    if(shmid == -1) 
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(2);//共享内存申请失败直接退出
    }
    printf("shmid:%d\n", shmid);

    //2.挂接共享内存
    void* addr = shmat(shmid, nullptr, 0);//返回起始地址当数组处理,
    if((long long)addr == -1l)//linux指针是八个字节
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(2);
    }
     char* start = (char*)addr;//当数组处理

    
    //3.通信

    //通信
    while(coun > 10)
    {
        printf("client:%s\n", start);
        sleep(1);
    }

    sleep(5);
    //4.取消挂接共享内存(不可以直接暴力删除,先去挂接)
    int deaddr = shmdt(start);
    if(deaddr == -1)
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(3);
    } 

    //5.删除共享内存
    int del = shmctl(shmid, IPC_RMID, nullptr);
    if(del == -1)
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
    }
    
    return 0;
}