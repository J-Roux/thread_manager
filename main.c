#include "src/thread_manager.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <time.h>




void Wait(double delta)
{
        clock_t expire = clock() + delta * CLOCKS_PER_SEC;
        while (clock() < expire) {
        }
}




void f1()
{
        DECLARE_AREA;
        uint8_t a;
        uint8_t i;
        END_DECLARE_AREA;
        BEGIN_THREAD;
        for( THIS.i = 0; THIS.i < 20; THIS.i++)
        {
                printf("hi\n");
                WAIT_FOR(0, 100, 0);
        }
        END_THREAD;
}



void f2()
{
        DECLARE_AREA;
        uint8_t a;
        uint8_t i;
        END_DECLARE_AREA;
        BEGIN_THREAD;
        for(THIS.i = 0; THIS.i < 20; THIS.i++)
        {
                printf("hello\n");
                Wait(0.05);
                YIELD;
        }
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
