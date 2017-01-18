#include "thread_manager.h"






void f1()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 7;
    YIELD;
        Serial.println(THIS.a);
    YIELD;
        Serial.println(THIS.a);
    END_THREAD;
}


void f2()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 5;
    YIELD;
        Serial.println(THIS.a);
    YIELD;
        Serial.println(THIS.a);
    END_THREAD;
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
