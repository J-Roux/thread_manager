#include "event.h"
#include "stddef.h"





Event::Event() {}

Event::Event(clock_t timeOut) : timeOut(clock() + timeOut){}

Event::Event(Callback callback, void *args, clock_t timeOut):
    callback(callback),
    args(args),
    timeOut(clock() + timeOut)
{}

bool Event::isSet()
{
    bool result;
    if(callback == NULL)
    {
        result = callback(args);
        if(!result && timeOut)
            result = CheckTimeOut();
    }
    else
    {
        result = CheckTimeOut();
    }
    return result;
}

bool Event::CheckTimeOut()
{
    return timeOut < clock();
}
