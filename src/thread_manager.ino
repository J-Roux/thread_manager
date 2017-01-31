#include "thread_manager.h"






void f1(uint8_t * arg)
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 7;
    YIELD;
    //    Serial.println(THIS.a);
    YIELD;
    //    Serial.println(THIS.a);
    END_THREAD;
}


void f2(uint8_t * arg)
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 5;
    YIELD;
    //    Serial.println(THIS.a);
    YIELD;
    //    Serial.println(THIS.a);
    END_THREAD;
}

void setup()
{
    uint8_t stack_one[STACK_SIZE];
    uint8_t stack_two[STACK_SIZE - 10];
    create_thread(&f1, 0, stack_one, thread_priotity_idle);
    create_thread(&f2, 0, stack_two, thread_priotity_idle);
    thread_manager();
    //Serial.println("end kernel");
    return 0;
}

void loop()
{

}
