#include "src/thread_manager.h"
#include <stdint.h>
#include <stdio.h>








void f1()
{
    DECLARE_AREA;
        uint8_t a;
        uint8_t i;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 1;
        for (THIS.i = 0; THIS.i < 4; THIS.i++)
        {

            case 23:
            {
            _yield((uint8_t*)&_thread_context, sizeof(_thread_context), &(_thread_context.pc), 23 + 1);
            goto f1;
            }
            case 23 + 1: {}
            printf("\n%u", THIS.a);
        }

    END_THREAD;
f1 :;
}

void f3()
{
    DECLARE_AREA;
    uint8_t b;
    END_DECLARE_AREA;
    BEGIN_THREAD;
    THIS.b = 3;
    YIELD;
    printf("\n%u", THIS.b);
    YIELD;
    printf("\n%u", THIS.b);
    set_end(true);
    END;
}


void f2()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 2;
        YIELD;
        int b = 0;
        printf("\n%u", THIS.a);
    CALL(f3());
    YIELD;
    printf("\n%u", THIS.a);

    END_THREAD;
}

#include <time.h>

//struct timeval difftime_ext(clock_t start, clock_t end)
//{
//    return
//}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef struct
{
    uint16_t sec     : 10;
    uint16_t usec    : 10;
    uint16_t micsec  : 10;
} time_interval;


time_interval get_time_interval(const clock_t start, const clock_t end)
{
    time_interval interval;
    double dur = 1000.0 * ( end - start) / CLOCKS_PER_SEC;
    interval.sec = dur / 1000;
    interval.usec = (long)dur % 1000;
    interval.micsec = (dur - (long)(dur)) * 1000;
    return interval;
}

bool greater_interval(const time_interval t1, const time_interval t2)
{
    bool result = false;
    if(t1.sec > t2.sec)
        result = true;
    else if(t1.usec > t2.usec)
        result = true;
    else if(t1.micsec > t2.micsec)
        result = true;
    return result;
}

#define WAIT_FOR(SEC, USEC, MICRO_SEC) start_timer(SEC, USEC, MICRO_SEC); YIELD;

int main()
{
//    uint8_t stack_one[STACK_SIZE];
//    uint8_t stack_two[STACK_SIZE - 10];
//    create_thread(&f1, 0, stack_one, thread_priotity_idle);
//    create_thread(&f2, 0, stack_two, thread_priotity_idle);
//    thread_manager();
//    puts("\nend thread manager");

    clock_t t1 = clock();

    for(size_t i = 0; i < 500000; i++);

    clock_t t2 = clock();

    time_interval val = get_time_interval(t1, t2);
    double dur = 1000.0 * ( t2 - t1) / CLOCKS_PER_SEC;
    time_interval val1 = { .sec = 0, .usec = 1, .micsec = 960 };
    bool res = greater_interval(val, val1);
    bool res1 = greater_interval(val1, val);
    printf("CPU time used (per clock(): %f ms\n", dur);
    printf("my func sec = %i, usec = %i, micsec = %i\n", val.sec, val.usec, val.micsec);
    printf("%i  %i\n",res, res1);

    return 0;
}
