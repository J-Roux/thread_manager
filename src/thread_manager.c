#include "thread_manager.h"

typedef enum
{
    TERMINATE,
    INIT,
    RUNNING
} thread_state;

typedef struct
{
    uint8_t             state       : 3;
    uint8_t             priority    : 4;
    bool                end_flag    : 1;
    uint8_t             errno          ;
}   thread_info;

typedef struct
{
    func_ptr            ptr;
    uint8_t             *stack_pointer;
    uint8_t             *args;
    thread_info         info;
} thread_context;





static thread_context   threads[MAX_THREAD_COUNT];
static uint8_t          current_id;
static uint8_t          thread_num                  = 0;

void terminate_thread()
{
    threads[get_id()].info.state = TERMINATE;
}


uint8_t get_id()
{
    return current_id;
}


void save_context(const uint8_t* ptr, const uint8_t size)
{
    push(ptr, size);
}

void _yield(uint8_t* context, uint8_t size, uint32_t *pc, uint32_t line)
{
    if(*pc > 0)
        pop(size);
    *pc = line;
    save_context(context, size);
    reset();
}




void load_context(uint8_t* ptr, const uint8_t size)
{
    if(threads[current_id].info.state == INIT)
        threads[current_id].info.state = RUNNING;
    if( is_next_stack_frame_exist(size))
        load(ptr, size);
}





int create_thread(const func_ptr func,
                  uint8_t *args,
                  uint8_t *stack_pointer,
                  thread_priority priority)
{
    int errno;
    for(uint8_t i = 0; i < MAX_THREAD_COUNT; i++)
    {
        if(threads[i].ptr == 0)
        {
            threads[i].info.priority       = priority;
            threads[i].info.state          = INIT;
            threads[i].info.end_flag       = false;
            threads[i].ptr                 = func;
            threads[i].args                = args;
            threads[i].stack_pointer       = stack_pointer; //TO DO: stack to id
            errno                          = 0;
            allocate_stack(stack_pointer, i);
            thread_num++;
            break;
        }
    }
    return errno;

}



bool is_end()
{
    return threads[current_id].info.end_flag;
}

void set_end(const bool val)
{
    threads[current_id].info.end_flag = val;
}

void thread_manager()
{
    init_stack();
    uint8_t dead_thread = 0;
    for(int i = 0; ;i = (++i % (thread_num ) ))
    {
        if(threads[i].info.state != TERMINATE)
        {
            current_id = i;
            threads[i].ptr(threads[i].args);
        }
        else
        {
            threads[i].ptr = 0;
            dead_thread++;
        }
        if(dead_thread == thread_num + 1)
        {
          break;
        }
        if(i == thread_num)
          dead_thread = 0;
    }
    thread_num = 0;
}
