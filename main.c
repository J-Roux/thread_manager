#include "src/thread_manager.h"
#include <stdint.h>
#include <stdio.h>








void f1()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 1;
    YIELD;
        printf("\n%u", THIS.a);
    YIELD;
        printf("\n%u", THIS.a);
    YIELD;
        printf("\n%u", THIS.a);
    YIELD;
        printf("\n%u", THIS.a);
    END_THREAD;
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
