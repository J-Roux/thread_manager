#include "thread_manager.h"



REGISTER(f1);
REGISTER(f2);




void f1()
{
   YIELD(_f1);
   Serial.println("f1 one");
   YIELD(_f1);
   Serial.println("f1 two");
   END_THREAD;
}

void f2()
{
   YIELD(_f2);
   Serial.println("f2 one");
   YIELD(_f2);
   Serial.println("f2 two");
   END_THREAD;
}



void setup()
{
    Serial.begin(9800);
    jmp_buf_ptr constexts[2] = { &_f1, &_f2};
    Func  func_array[2] = { &f1, &f2};
    kernel(constexts,func_array, 2);
    Serial.println("end kernel");
    return 0;
}

void loop()
{

}
