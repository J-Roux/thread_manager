#include "threadManager.hpp"



class ThreadOne : public Thread
{
    uint8_t i;
public:
    ThreadOne() : i(0), Thread() {}
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
    WatchDog() : Thread() {}
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




int main()
{
    ThreadOne thread1;
    WatchDog watchDog;
    ThreadManager<2> manager;
    manager.threads[0] = &thread1;
    manager.threads[1] = &watchDog;
    manager.loop();
    return 0;
}
