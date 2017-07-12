#include "threadManager.hpp"
#include "stack.h"






class ThreadOne : public Thread
{
    uint8_t i;
public:
    ThreadOne(IStack<uint32_t> *stack) : i(0), Thread(stack) {}
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

class WatchDog : public Thread
{
public:
    WatchDog(IStack<uint32_t> *stack) : Thread(stack) {}
    virtual void operator ()()
    {
        BEGIN_THREAD;
        for(;;)
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
