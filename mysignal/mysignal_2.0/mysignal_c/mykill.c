
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <string.h>


//kill 给任何进程方式任何信号
//不满足要求启动提示
void Usage(const char* proc)
{
    printf("启动：./kill -0 12345\n");
}

//./kill -2(信号) 12345(进程)
int main(int argc, char* argv[]) //通过命令行传参。
{
    if(argc != 3)
    {
        Usage(argv[0]);
        exit(-1);
    }

    //解析命令行参数，记录好
    pid_t pid = atoi(argv[2]);
    int sig = atoi(argv[1]);

    int k = kill(pid, sig);
    if(k != 0)
    {
        perror("kill");
    }
    return 0;
}