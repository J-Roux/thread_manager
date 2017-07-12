#include "thread.hpp"


Thread::Thread(IStack<uint32_t> *stack) :
    pc(0),
    state(INIT),
    priority(0),
    errorNumber(0),
    endTime(0),
    stack(stack)
{
}


ThreadState Thread::GetState() const
{
    return (ThreadState)state;
}

void Thread::SetTimer(clock_t endTime)
{
    this->endTime = endTime;
    this->state = WAIT;
}

void Thread::IsWaiting()
{
    if(this->endTime < clock())
    {
        this->endTime = 0;
        this->state = RUNNING;
    }
}


