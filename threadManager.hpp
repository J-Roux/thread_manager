#pragma once

#include "thread.hpp"


#define BEGIN_THREAD      switch(this->pc) { case 0:{ this->state = RUNNING;}
#define END_THREAD         } this->state = TERMINATE;
#define YIELD             case __COUNTER__: this->pc = __COUNTER__ + 1; return; case __COUNTER__:

#define WAIT_FOR(SEC, USEC, MICRO_SEC) StartTimer(SEC, USEC, MICRO_SEC); YIELD;


const uint8_t Zero = __COUNTER__;



template<uint8_t threadNumber>
class ThreadManager
{
    uint8_t iter;

    bool isThreadsAlive()
    {
        bool isEnd = true;
        for(uint8_t i = 0; i < threadNumber; i++)
        {
            isEnd &= threads[i] == NULL;
        }
        return isEnd;
    }


public:
    ThreadManager() : iter(0) {}
    Thread *threads[threadNumber];

    void loop()
    {
        for(uint8_t i = 0;; i++)
        {
            iter = i % threadNumber;
            Thread* currentThread = threads[iter];
            if(currentThread)
            {
                switch (currentThread->getState()) {
                case WAIT:
                {
                    currentThread->IsThreadReady();
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

