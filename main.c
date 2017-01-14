#include "main.h"



REGISTER(f1);
REGISTER(f2);




void f1()
{
   YIELD(_f1);
   printf("\nf1 one");
   YIELD(_f1);
   printf("\nf1 two");
   END_THREAD;
}

void f2()
{
   YIELD(_f2);
   printf("\nf2 one");
   YIELD(_f2);
   printf("\nf2 two");
   END_THREAD;
}



int main()
{
    jmp_buf_ptr constexts[2] = { &_f1, &_f2};
    Func  func_array[2] = { &f1, &f2};
    kernel(constexts,func_array, 2);
    puts("\nend thread manager");
    return 0;
}
