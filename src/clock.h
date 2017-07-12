#ifndef _CLOCK
#define _CLOCK

#include <stdint.h>
#include <stdbool.h>





#if defined(__x86_64__) || defined(__i386__)
        #include <time.h>
#else

typedef uint64_t clock_t;

#ifdef __cplusplus
extern "C" {
#endif

clock_t clock();

#ifdef __cplusplus
}
#endif

#define CLOCKS_PER_SEC 1000000

#endif



#endif
