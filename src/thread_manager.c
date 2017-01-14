#include "thread_manager.h"



jmp_buf kernel_context;

int _end_thread = 0;


void end_thread()
{
    _end_thread++;
}

jmp_buf_ptr get_kernel_context()
{
    return &kernel_context;
}

void kernel(jmp_buf_ptr* contexts, Func * funcs, int len)
{
    for(int i = 0; i < len; i++)
    {
        if(setjmp(kernel_context) == 0)
            funcs[i]();
    }
    for(int i = 0;; )
    {
        if (setjmp(kernel_context) != 0)
            i =  (i + 1) % len;
        if(_end_thread == len)
                break;
        longjmp(*contexts[i], __COUNTER__);
    }
}
