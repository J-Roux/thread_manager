#include "main.h"




_THREAD(f1)
    DECLARE
        uint8_t a;
    END_DECLARE
    THIS.a = 5;
    printf("\n%u", THIS.id);
    YIELD; //@0x7fffffffe500
    printf("\nf1 one = %u", THIS.id);
    YIELD;
    printf("\nf1 two = %u", THIS.a);
    END_THREAD;
}

_THREAD(f2)
    DECLARE
        uint8_t b;
    END_DECLARE
    THIS.b = 6;
    printf("\n%u", THIS.id);
    YIELD;//@0x7fffffffe500
    printf("\nf2 one = %u",THIS.id);
    YIELD;
    printf("\nf2 two = %u", THIS.b);
    END_THREAD;
}



int main()
{
    create_thread(f1, 0, 0);
    create_thread(f2, 0, 0);
    thread_manager();
    puts("\nend thread manager");
    return 0;
}
