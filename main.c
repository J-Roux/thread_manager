#include "src/thread_manager.h"
#include <stdint.h>
#include <stdio.h>


bool is_init[MAX_THREAD_COUNT];

#define THIS _thread_context
#define DECLARE_AREA struct { \
    uint32_t pc \

#define END_DECLARE_AREA } _thread_context;\
_thread_context.pc = 0;\
load_context((uint8_t*)&_thread_context, sizeof(_thread_context))\

void f1()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    switch (_thread_context.pc)
    {
    case 0:
    {
        THIS.a = 7;
    }
    case __LINE__: _thread_context.pc = __LINE__ + 2;
        save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {

        printf("\n%u", THIS.a);
    }
    case __LINE__: _thread_context.pc = __LINE__ + 2;
        save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        printf("\n%u", THIS.a);
    }
    }
    set_end(true);
    terminate_thread();
}

void f3()
{
    DECLARE_AREA;
        uint8_t b;
    END_DECLARE_AREA;
    switch (_thread_context.pc)
    {
    case 0:
    {
        THIS.b = 8;
    }
    case __LINE__: _thread_context.pc = __LINE__ + 2;
        save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        printf("\n%u", THIS.b);

    }
    case __LINE__: _thread_context.pc = __LINE__ + 2;
        save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        printf("\n%u", THIS.b);
    }
    }
    set_end(true);
}

void f2()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    switch (_thread_context.pc)
    {
    case 0:
    {
        THIS.a = 5;

    }
    case __LINE__: _thread_context.pc = __LINE__ + 2;
        save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        printf("\n%u", THIS.a);
    }

    case __LINE__: _thread_context.pc = __LINE__;
        save_context((uint8_t*)&_thread_context, sizeof(_thread_context));
        f3();
        if(is_end())
        {
            set_end(false);
            _thread_context.pc = __LINE__ + 3;
        }
        load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
    case __LINE__: {}


    case __LINE__: _thread_context.pc = __LINE__ + 2;
        save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        printf("\n%u", THIS.a);
    }
    }
    set_end(true);
    terminate_thread();
}



int main()
{
    create_thread(&f1);
    create_thread(&f2);
    thread_manager();
    puts("\nend thread manager");
    return 0;
}
