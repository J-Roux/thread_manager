#ifndef _CLOCK
#define _CLOCK

#include <stdint.h>
#include <stdbool.h>

#if defined(__x86_64__) || defined(__i386__)
        #include <time.h>
#else

typedef uint64_t clock_t;

clock_t clock();

#define CLOCKS_PER_SEC 1000000

#endif



#pragma pack(2)
typedef struct
{
        uint16_t sec        : 10;
        uint16_t usec       : 10;
        uint16_t micro_sec  : 10;
} time_interval;
#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif
time_interval get_time_interval(const clock_t* start, const clock_t* end);

bool greater_interval(const time_interval* t1, const time_interval* t2);

#ifdef __cplusplus
}
#endif
#endif
