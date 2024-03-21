#include <string>
#include <pthread.h>
#include <functional>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cassert>


class Thread;

//上下文,当成一个大号的结构体
class Context
{
public:
    Thread *this_;
    void *args_;
public:
    Context():this_(nullptr), args_(nullptr)
    {}
    ~Context()
    {}
};

class Thread
{
public:
    // using func_t = std::function<void*(void*)>;
    typedef std::function<void*(void*)> func_t;
    const int num = 1024;
public:
    
    //func要执行的函数
    //args 线程执行的参数
    //线程的id
    Thread(func_t func, void *args = nullptr, int number = 0): func_(func), args_(args)
    {
        // name_ = "thread-";
        // name_ += std::to_string(number);

        char buffer[num];
        snprintf(buffer, sizeof buffer, "thread-%d", number);
        name_ = buffer;

         // 异常 == if: 意料之外用异常或者if判断
        // assert: 意料之中用assert
        Context *ctx = new Context();
        ctx->this_ = this;
        ctx->args_ = args_;
        int n = pthread_create(&tid_, nullptr, start_routine, ctx); //TODO
        assert(n == 0); 
        (void)n;
    }
    // 在类内创建线程，想让线程执行对应的方法，需要将方法设置成为static
    static void *start_routine(void *args) //类内成员，有缺省参数！
    {
        Context *ctx = static_cast<Context *>(args);
        void *ret = ctx->this_->run(ctx->args_);
        delete ctx;
        return ret;
        // 静态方法不能调用成员方法或者成员变量
    }

    void join()
    {
        int n = pthread_join(tid_, nullptr);   //不管自己的id
        assert(n == 0);
        (void)n;
    }

    void *run(void *args)
    {
        return func_(args);
    }

    ~Thread()
    {
        //do nothing
    }
private:
    std::string name_;  //线程有自己的名字
    func_t func_;       //要做什么工作的函数
    void *args_;        //线程执行的参数

    pthread_t tid_;     //线程的id
};