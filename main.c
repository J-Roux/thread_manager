#include "src/thread_manager.h"
#include <stdint.h>
#include <stdio.h>



void yield(uint8_t* context, uint8_t size, uint8_t *pc, uint32_t line)
{
    if(*pc > 0)
        pop(size);
    *pc = line;
    save_context(context, size);
    reset();
}





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
        pop(sizeof(_thread_context)); // pop only if yield
    }
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
    create_thread(&f1);
    create_thread(&f2);
    thread_manager();
    puts("\nend thread manager");
    return 0;
}
