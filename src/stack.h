#ifndef STACK_H
#define STACK_H
#include "stdint.h"

template<typename T>
class IStack
{
public:
    virtual bool Push(T pc) = 0;
    virtual bool Pop(T &pc) = 0;
};

template<uint16_t stackSize, typename T>
class Stack : public IStack<T>
{
    T data[stackSize];
    uint16_t counter;
public:
    Stack(): data(), counter(0)  {}
    virtual bool Push(T pc)
    {
        bool result = false;
        if(counter + 1 < stackSize)
        {
            data[++counter] = pc;
            result = true;
        }
        return result;
    }

    virtual bool Pop(T &pc)
    {
        bool result = false;
        if(counter - 1 >= 0)
        {
            pc = data[counter--];
            result = true;
        }
        return result;
    }
};




#endif // STACK_H


