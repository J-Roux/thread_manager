#include "src/thread_manager.h"
#include <stdint.h>
#include <stdio.h>





void f1()
{
    DECLARE_AREA;
        uint8_t a;
    } _thread_context;
    _thread_context.pc = 0;
    load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
    BEGIN_THREAD;
        THIS.a = 1;
        case 1: {_thread_context.pc = 2;
                      reset();
                      if(is_next_stack_frame_exist(sizeof(_thread_context)))
                          pop(sizeof(_thread_context));
                      save_context((uint8_t*)&_thread_context, sizeof(_thread_context));
                      break;
                      }
                      case 2:

        printf("\n%u", THIS.a);
        case 3: {_thread_context.pc = 4;
                      reset();
                      if(is_next_stack_frame_exist(sizeof(_thread_context)))
                          pop(sizeof(_thread_context));
                      save_context((uint8_t*)&_thread_context, sizeof(_thread_context));
                      break;
                      }
                      case 4:

        printf("\n%u", THIS.a);
    END_THREAD;
}

void f3()
{
    DECLARE_AREA;
        uint8_t b;
    } _thread_context;
    _thread_context.pc = 0;
    load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
    BEGIN_THREAD;
        THIS.b = 3;
        case 1: {_thread_context.pc = 2;
                      reset();
                      if(is_next_stack_frame_exist(sizeof(_thread_context)))
                          pop(sizeof(_thread_context));
                      save_context((uint8_t*)&_thread_context, sizeof(_thread_context));
                      break;
                      }
                      case 2:


        printf("\n%u", THIS.b);
        case 3: {_thread_context.pc = 4;
                      reset();
                      if(is_next_stack_frame_exist(sizeof(_thread_context)))
                          pop(sizeof(_thread_context));
                      save_context((uint8_t*)&_thread_context, sizeof(_thread_context));
                      break;
                      }
                      case 4:

        printf("\n%u", THIS.b);
        set_end(true);
        pop(sizeof(_thread_context));
    }
}


void f2()
{
    DECLARE_AREA;
        uint8_t a;
    } _thread_context;
    _thread_context.pc = 0;
    load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
    BEGIN_THREAD;
        THIS.a = 2;
        case 1: {_thread_context.pc = 2;
                      reset();
                      if(is_next_stack_frame_exist(sizeof(_thread_context)))
                          pop(sizeof(_thread_context));
                      save_context((uint8_t*)&_thread_context, sizeof(_thread_context));
                      break;
                      }
                      case 2:

        printf("\n%u", THIS.a);

        case 299: _thread_context.pc = 300;
        if(THIS.pc > 0)
            pop(sizeof(_thread_context));
        save_context((uint8_t*)&_thread_context, sizeof(_thread_context));
        case 300: f3();
        if(!is_end())
        {
            reset();
            break;
        }
        else
        {
            set_end(false);
            load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
        }

        case 3: {_thread_context.pc = 4;
                      reset();
                      if(is_next_stack_frame_exist(sizeof(_thread_context)))
                          pop(sizeof(_thread_context));
                      save_context((uint8_t*)&_thread_context, sizeof(_thread_context));
                      break;
                      }
                      case 4:

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
