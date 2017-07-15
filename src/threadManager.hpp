#pragma once

#include "thread.hpp"
#include "stddef.h"

#define BEGIN_THREAD      switch(this->pc) { case 0:{ this->state = RUNNING;}
#define END_THREAD         } this->state = TERMINATE;
#define YIELD             case __COUNTER__: this->pc = __COUNTER__ + 1; return; case __COUNTER__:

#define WAIT_FOR(SEC, MSEC, USEC) this->SetEvent(Event(timeToClock(SEC, MSEC, USEC)));  \
                                                YIELD;

clock_t timeToClock(uint32_t sec, uint32_t msec, uint32_t usec);

const uint8_t Zero = __COUNTER__;




template<uint8_t threadNumber>
class ThreadManager
{
    uint8_t iter;

    bool isThreadsAlive() const
    {
        bool isEnd = true;
        for(uint8_t i = 0; i < threadNumber; i++)
        {
            isEnd &= threads[i] == NULL;
        }
        return isEnd;
    }

    IThread *threads[threadNumber];
public:
    ThreadManager() : iter(0), threads() {}

    bool CreateThread(IThread* thread)
    {
        for(uint8_t i = 0; i < threadNumber; i++)
        {
            if(!this->threads[i])
            {
                this->threads[i] = thread;
                return true;
            }
        }
        return false;
    }

    void loop()
    {
        for(uint8_t i = 0;; i++)
        {
            iter = i % threadNumber;
            IThread* currentThread = threads[iter];
            if(currentThread)
            {
                switch (currentThread->GetState()) {
                case INIT:
                case RUNNING: (*currentThread)();  break;
                case WAIT:
                {
                    currentThread->IsWaiting();
                    break;
                }
                case TERMINATE:{
                     threads[iter] = NULL;
                }
                }
            }
            else
            {
                if(isThreadsAlive())
                    return;
            }
        }
    }

};

