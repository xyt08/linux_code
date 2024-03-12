#ifndef _SHM_C_
#define _SHM_C_

//c
#include <stdio.h>
#include <errno.h>
#include <string.h>
//系统
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

//宏
#define PATHNAME "."    //定义文件路径
#define PROJ_ID 0x66    //定义id
#define MAX_SIZE 4096   //定义空间大小

//封装一个接口,来获取key
key_t getkey()
{
    key_t k = ftok(PATHNAME, PROJ_ID);
    if(k < 0)
    {
        printf("key值获取失败: errno:%d %s\n",errno, strerror(errno));
        exit(-1);
    }
    return k;
}


//不管是创建共享还是获取,都要shmget,直接封装一个公共接口
int getshmhelp(key_t k, int shmflg)
{
    int shmid = shmget(k, MAX_SIZE, shmflg);
    if(shmid < 0)
    {
        printf("共享内存创建失败 errno:%d %s",errno, strerror(errno));
        exit(-1);
    }
    return shmid;
}

//创建共享内存
int create_shm(key_t k)
{
    return getshmhelp(k, IPC_CREAT | IPC_EXCL | 0660);
}

//获取共享内存
int get_shm(key_t k)
{
    return getshmhelp(k, IPC_CREAT);//可以填了"0"
}

void deshmctl(int shmid)
{
    if((shmctl(shmid, IPC_RMID, NULL)) == -1)
    {
        printf("删除失败  errno %d %s:\n",errno, strerror(errno));
        exit(-1);
    }
}

void* attachshmat(int shmid)
{
    void* ret = shmat(shmid, NULL, 0);
    if((long long)ret < 0)
    {
        printf("挂接失败:errno %d %s\n", errno, strerror(errno));
        exit(-1);
    }
    return ret;
}

void detashmdt(void* addr)
{
    if((shmdt(addr)) < 0 )
    {
        printf("去关联失败 errno %d %s:\n",errno, strerror(errno));
    }
}

#endif