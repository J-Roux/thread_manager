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




int main()
{
    uint8_t stack_one[STACK_SIZE];
    uint8_t stack_two[STACK_SIZE - 10];
    create_thread(&f1, 0, stack_one, thread_priotity_idle);
    create_thread(&f2, 0, stack_two, thread_priotity_idle);
    thread_manager();
    puts("\nend thread manager");

    return 0;
}
