#include "clock.h"

#if !defined(__x86_64__) && !defined(__i386__)

clock_t clock()
{
        return 0;
}

#endif

