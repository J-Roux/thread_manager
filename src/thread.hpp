


#include "stack.h"
#include "event.h"

typedef enum
{
    TERMINATE,
    INIT,
    WAIT,
    RUNNING
} ThreadState;









class IThread
{
protected:
    uint32_t            pc;
    uint8_t             state       : 3;
    uint8_t             priority    : 4;
    uint8_t             errorNumber    ;
    Event              event;
    IStack<uint32_t>    *stack;
public:

    IThread(IStack<uint32_t> *stack);
    ThreadState GetState() const;
    void SaveContext();
    void LoadContext();
    void SetEvent(const Event &event);
    void IsWaiting();
    virtual void operator()() = 0;
    virtual ~IThread(){}


};
