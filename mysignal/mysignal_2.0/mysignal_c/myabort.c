

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


// int main()
// {
//     int k = 0;
//     while(k <= 10)
//     {
//         printf("k:%d", k++);
//         sleep(1);
//         if(k = 5)
//         {
//             abort();    //abort();的abort使用
//         }
    
//     }
//     return 0;
// }



int main()
{
    int k = 0;
    while (k <= 10)
    {
        printf("k : %d", k++);
        sleep(1);
        if(k >= 5)
        {
            kill(getpid(),  SIGABRT);   //用kill实现对abort的封装
        }
    }
    return 0;
}