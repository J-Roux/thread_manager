#include "thread.hpp"


IThread::IThread(IStack<uint32_t> *stack) :
    pc(0),
    state(INIT),
    priority(0),
    errorNumber(0),
    stack(stack)
{
}


ThreadState IThread::GetState() const
{
    return (ThreadState)state;
}

void IThread::SaveContext()
{

}

void IThread::LoadContext()
{

}

void IThread::SetEvent(const Event &event)
{
    this->event = event;
    this->state = WAIT;
}


void IThread::IsWaiting()
{
    if(event.isSet())
    {
        this->state = RUNNING;
    }
}


