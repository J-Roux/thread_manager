#include "threadManager.hpp"



class ThreadOne : public Thread
{
    uint8_t i;
public:
    ThreadOne() : Thread(), i(0) {}
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
    ThreadOne thread1;
    WatchDog watchDog;
    ThreadManager<2> manager;
    manager.threads[0] = &thread1;
    manager.threads[1] = &watchDog;
    manager.loop();
}

void loop()
{

}
