#include "thread_manager.h"






void f1()
{
    struct {
        uint32_t pc;
        uint8_t a;

    } _thread_context;
    _thread_context.pc = 0;
    load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
    switch (_thread_context.pc)
    {
    case 0:
    {
        _thread_context.a = 7;
    }
    case __LINE__: _thread_context.pc = __LINE__ + 1; save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {

        Serial.println(_thread_context.a);
    }
    case __LINE__: _thread_context.pc = __LINE__ + 1; save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        Serial.println( _thread_context.a);
    }
    }
}


void f2()
{
    struct {
        uint32_t pc;
        uint8_t a;

    } _thread_context;
    _thread_context.pc = 0;
    load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
    switch (_thread_context.pc)
    {
    case 0:
    {
        _thread_context.a = 5;

    }
    case __LINE__: _thread_context.pc = __LINE__ + 1; save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        Serial.println( _thread_context.a);
    }

    case __LINE__: _thread_context.pc = __LINE__ + 1; save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        Serial.println(_thread_context.a);
    }
    }
}

void setup()
{
    create_thread(&f1);
    create_thread(&f2);
    thread_manager();
    Serial.println("end kernel");
    return 0;
}

void loop()
{

}
