
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// void test1() //使用raise()给自己发任意一个信号
// {
//     int c = 0;
//     while(c <= 10)
//     {
//         printf("hello workd c: %d\n", c++);
//         if(c >= 5)
//         {
//             raise(3);
//         }
//         sleep(1);
//     }
// }

void test2() // kill实现raise
{
    int c = 0;
    while (c <= 10)
    {
        printf("hello workd c: %d\n", c++);
        if (c >= 5)
        {
            kill(getpid(), 3);  //直接
        }
        sleep(1);
    }
}

int main()
{
    test1();
}