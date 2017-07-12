#pragma once

#include "thread.hpp"
#include "stddef.h"

#define BEGIN_THREAD      switch(this->pc) { case 0:{ this->state = RUNNING;}
#define END_THREAD         } this->state = TERMINATE;
#define YIELD             case __COUNTER__: this->pc = __COUNTER__ + 1; return; case __COUNTER__:

#define WAIT_FOR(SEC, USEC, MICRO_SEC) SetTimer(clock() + \
                                                clock_t((float(SEC) + \
                                                         float(USEC / 1000) + \
                                                         float(MICRO_SEC / 1000000)) * \
                                                CLOCKS_PER_SEC));  \
                                                YIELD;


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

    Thread *threads[threadNumber];
public:
    ThreadManager() : iter(0), threads() {}

    bool CreateThread(Thread* thread)
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
            Thread* currentThread = threads[iter];
            if(currentThread)
            {
                switch (currentThread->GetState()) {
                case WAIT:
                {
                    currentThread->IsWaiting();
                    break;
                }
                case INIT:
                case RUNNING: (*currentThread)();  break;
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

