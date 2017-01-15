#include "main.h"




_THREAD(f1)
   static int a = 5;
   printf("\n%u", _id);
   YIELD; //@0x7fffffffe500
   printf("\nf1 one = %u", _id);
   YIELD;
   printf("\nf1 two = %u", a);
   end_thread(_id);
}

_THREAD(f2)
   static int b = 6;
   printf("\n%u", _id);
   YIELD;//@0x7fffffffe500
   printf("\nf2 one = %u", _id);
   YIELD;
   printf("\nf2 two = %u", b);
   end_thread(_id);
}



int main()
{
    create_thread(f1, 0, 0);
    create_thread(f2, 0, 0);
    thread_manager();
    puts("\nend thread manager");
    return 0;
}
