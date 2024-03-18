

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

//多线程1.0

void* thread_routine(void* arg)
{
    const char* buff = (char*)arg;
    while(1)
    {
        printf("%s\n",buff);
        sleep(1);
    }
}

void test()
{
    pthread_t id;
    int a = pthread_create(&id, NULL, thread_routine, (void*)"我是新线程");
    assert(a == 0);
    (void)a;

    while(1)
    {
        printf("我是主线程\n");
        sleep(1);
    }
}

int main()
{
    test();
    return 0;
}




