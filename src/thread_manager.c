#include "thread_manager.h"

#include <time.h>
typedef enum
{
    NOT_INIT,
    RUNNING,
    END
} thread_state;


typedef struct
{
    func_ptr ptr;
    thread_state state;
    uint8_t argc;
    void * argv;
} thread_context;



thread_context threads[MAX_THREAD_COUNT];
static jmp_buf_ptr contexts[MAX_THREAD_COUNT];
uint8_t pointer = 0;

jmp_buf kernel_context;

int _end_thread = 0;




uint8_t create_thread(func_ptr ptr, uint8_t argc, void* argv)
{
    if(pointer < MAX_THREAD_COUNT)
    {
        threads[pointer].argc = argc;
        threads[pointer].argv = argv;
        threads[pointer].ptr = ptr;
        threads[pointer].state = NOT_INIT;
        return pointer++;
    }
    else
    {
        return false;
    }
}


void add_context(jmp_buf_ptr context, uint8_t id)
{
    contexts[id] = context;
}

jmp_buf_ptr get_context(uint8_t id)
{
    return contexts[id];
}

jmp_buf_ptr get_kernel_context()
{
    return &kernel_context;
}





void end_thread(uint8_t id)
{
    threads[id].state = END;
    longjmp(*get_kernel_context(), __COUNTER__);
}

void thread_manager()
{
    for(int i =0;; i =(++i % pointer))
    {
        thread_context thread = threads[i];
        switch (thread.state)
        {
        case NOT_INIT:
            threads[i].state = RUNNING;
            if (setjmp(kernel_context) == 0)
                thread.ptr(i, thread.argc, thread.argv);
            break;
        case RUNNING:
            if (setjmp(kernel_context) == 0)
                longjmp(*get_context(i), __COUNTER__);
            break;
        case END:
            _end_thread++;
            break;
        }

        if(_end_thread == 2)
            break;
    }
}
