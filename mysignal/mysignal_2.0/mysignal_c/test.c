#include <stdio.h>
#include <unistd.h>
#include <signal.h>


// int main()
// {
//     //一直在运行,方便后面的测试。配合mykill使用的
//     while(1)
//     {
//         printf("hello world pid: %d\n", getpid());
//         sleep(1);
//     }
//     return 0;
// }



// //和之前代码无关就是测试一下除0硬件产生的信号
// int main()
// {
//     printf("我正在运行......\n");
//     sleep(2);
//     int a = 1;
//     a = a/0;
//     return 0;
// }



void handler(int signal)
{
    printf("我补抓到的是%d信号\n", signal);
    sleep(1);
}

int main()
{
    signal(SIGFPE, handler); //对sigfpe进行捕捉。看看如我说的一样是。

    printf("我在运行.....\n");
    sleep(1);
    int a = 1;
    a = 1 / 0;
    return 0;
}
