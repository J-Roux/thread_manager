#include "threadManager.hpp"
#include "stack.h"






class ThreadOne : public IThread
{
    uint8_t i;
public:
    ThreadOne(IStack<uint32_t> *stack) :  IThread(stack), i(0){}
    virtual void operator ()()
    {
        BEGIN_THREAD;
        for(this->i; i < 5; this->i++ )
        {
            WAIT_FOR(10, 0, 0);
        }
        END_THREAD;
    }
    virtual ~ThreadOne() {}
};

class WatchDog : public IThread
{
public:
    WatchDog(IStack<uint32_t> *stack) : IThread(stack) {}
    virtual void operator ()()
    {
        BEGIN_THREAD;
        while(true)
        {
            WAIT_FOR(5, 0, 0);
        }
        END_THREAD;
    }
    virtual ~WatchDog() {}
};





void setup()
{
    Stack<16, uint32_t> stack;
    ThreadOne thread1(&stack);
    WatchDog watchDog(NULL);
    ThreadManager<2> manager;
    manager.CreateThread(&thread1);
    manager.CreateThread(&watchDog);
    manager.loop();
}

void loop()
{

}
