#include "thread.hpp"

ThreadState Thread::getState()
{
    return (ThreadState)state;
}

void Thread::StartTimer(uint16_t sec, uint16_t usec, uint16_t micro_sec)
{
        if((ThreadState)this->state != WAIT)
        {
                time_interval interval = { sec, usec, micro_sec };
                this->interval           = interval;
                this->start_time         = clock();
                this->state              = WAIT;
        }
}

void Thread::IsThreadReady()
{
        clock_t end = clock();
        time_interval interval = get_time_interval(&this->start_time, &end);
        if(greater_interval(&interval, &(this->interval)))
        {
                time_interval zero       = {0};
                this->state              = RUNNING;
                this->start_time         = 0;
                this->interval           = zero;
        }
}
