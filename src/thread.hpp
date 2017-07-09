

#include "clock.h"


typedef enum
{
        TERMINATE,
        INIT,
        WAIT,
        RUNNING
} ThreadState;




class Thread
{
protected:
    uint32_t pc;
    uint8_t             state       : 3;
    uint8_t             priority    : 4;
    uint8_t             errorNumber    ;
    clock_t             endTime;
public:

    Thread();
    ThreadState GetState() const ;
    void SetTimer(clock_t endTime);
    void IsWaiting();
    virtual void operator()() = 0;
    virtual ~Thread(){}


};
