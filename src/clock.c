#include "clock.h"

#if !defined(__x86_64__) && !defined(__i386__)

clock_t clock()
{
        return 0;
}

#endif

time_interval get_time_interval(const clock_t* start, const clock_t* end)
{
        time_interval interval;
        double dur         = 1000.0 * ( *end - *start) / CLOCKS_PER_SEC;
        interval.sec       = dur / 1000;
        interval.usec      = (long)dur % 1000;
        interval.micro_sec = (dur - (long)(dur)) * 1000;
        return interval;
}





bool greater_interval(const time_interval* t1, const time_interval* t2)
{
        bool result = false;
        if(t1->sec >= t2->sec && t1->usec >= t2->usec && t1->micro_sec >= t2->micro_sec)
                result = true;
        return result;
}


