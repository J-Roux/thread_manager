#include "threadManager.hpp"


clock_t timeToClock(uint32_t sec, uint32_t msec, uint32_t usec)
{
    return clock_t( (uint64_t(sec) * 1000000 + float(msec) * 1000 + float(usec)) * CLOCKS_PER_SEC / 1000000);
}
