
#include <iostream>
#include <unistd.h>
#include <signal.h>

// void handler(int signal)
// {
//     printf("我已经收到了二号信号");
// }

// void test_signo()
// {
//     int i = 0;
//     while(true)
//     {
//         printf("你好,我是一个进程,开始报数 %d\n", i++);
//         sleep(1);
//     }
// }

// int main()
// {
//     signal(2, handler);
//     test_signo();
//     return 0;
// }


void handler(int signal)
{
    std::cout << "我已经捕获到了" << signal << "信号"  << std::endl;
    //exit(1);
}

int main()
{
    //这里是signal函数的调用,并不是调用handler
    //这里仅仅是设置了对2号信号的捕捉方法,并不是代表该方法被调用了
    //一般这个方法不会被执行,除非收到了对应的信号
    signal(2, handler);
    while(true)
    {
        std::cout << "我是一个进程 pid:"<< getpid()<< std::endl;
        sleep(1);
    }
    
    return 0;
}