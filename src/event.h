#ifndef EVENT_H
#define EVENT_H

#include "clock.h"

typedef bool(*Callback)(void* args);

class Event
{
    Callback callback;
    void* args;
    clock_t timeOut;
    bool CheckTimeOut();
public:
    Event();
    Event(clock_t timeOut);
    Event(Callback callback, void* args, clock_t timeOut = 0);

    bool isSet();
    ~Event() {}

};

#endif // EVENT_H
