

#include "clock.h"
#include "stack.h"

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
    uint32_t            pc;
    uint8_t             state       : 3;
    uint8_t             priority    : 4;
    uint8_t             errorNumber    ;
    clock_t             endTime;
    IStack<uint32_t>     *stack;
public:

    Thread(IStack<uint32_t> *stack);
    ThreadState GetState() const ;
    void SetTimer(clock_t endTime);
    void IsWaiting();
    virtual void operator()() = 0;
    virtual ~Thread(){}


};
