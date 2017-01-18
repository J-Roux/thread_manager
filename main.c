#include "src/thread_manager.h"
#include <stdint.h>
#include <stdio.h>





void f1()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 7;
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
        THIS.b = 8;
    YIELD;
        printf("\n%u", THIS.b);
    YIELD;
        printf("\n%u", THIS.b);
        set_end(true);
        pop(sizeof(_thread_context));
    }
}

void f2()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 5;
    YIELD;
        printf("\n%u", THIS.a);
        _thread_context.pc = __LINE__; save_context((uint8_t*)&_thread_context, sizeof(_thread_context));} else if( _thread_context.pc == __LINE__) { _thread_context.pc = __LINE__;
        save_context((uint8_t*)&_thread_context, sizeof(_thread_context));
        f3();
        if(!is_end())
        {
        }
        load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
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
