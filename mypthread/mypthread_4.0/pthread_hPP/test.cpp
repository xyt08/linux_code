#include "pthread.hpp"
#include <iostream>
#include <memory>


void* thread_run(void* args)
{
    std::string work_type = static_cast<char*>(args);

    while(true)
    {
        std::cout<<"我是一个新线程，我正在做：" << work_type << std::endl;
        sleep(1);
    }
}

int main()
{
    std::unique_ptr<Thread> thread(new Thread(thread_run,  (void*)"hello_pthread", 0));    //创建一个线程对象。
    thread->join(); //线程等待
    return 0;
}