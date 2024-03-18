
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// 票的总数
int tickets = 10000;

void *pthread_routine(void *arg)
{
    while (1)
    {
        char *buff = (char *)arg;
        if (tickets > 0) // 有票就继续
        {
            printf("%s %d\n", buff, tickets--);
            usleep(1234);
        }
        else
        {
            break; // 没票了，就不能再抢了
        }
    }
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, pthread_routine, (void *)"我是乘客1,抢票");
    pthread_create(&tid, NULL, pthread_routine, (void *)"我是乘客2,抢票");
    pthread_create(&tid, NULL, pthread_routine, (void *)"我是乘客3,抢票");
    pthread_create(&tid, NULL, pthread_routine, (void *)"我是乘客4,抢票");

    pthread_join(tid, NULL);
    pthread_join(tid, NULL);
    pthread_join(tid, NULL);
    pthread_join(tid, NULL);

    return 0;
}