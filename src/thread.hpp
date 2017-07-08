

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
    clock_t             start_time     ;
    time_interval       interval       ;
public:

    Thread();
    ThreadState GetState();
    void StartTimer(uint16_t sec, uint16_t usec, uint16_t micro_sec);
    void IsThreadReady();
    virtual void operator()() = 0;
    virtual ~Thread(){}


};
