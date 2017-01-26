#include "thread_manager.h"

typedef enum
{
    TERMINATE,
    INIT,
    RUNNING
} thread_state;



typedef struct
{
    func_ptr            ptr;
    thread_state        state;
    uint8_t             *stack_pointer;
    uint8_t             *args;
    thread_priority     priority;
    bool end_flag;
} thread_context;





static thread_context   threads[MAX_THREAD_COUNT];
static uint8_t          current_id;
static uint8_t          thread_num                  = 0;

void terminate_thread()
{
    threads[get_id()].state = TERMINATE;
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
    if(threads[current_id].state == INIT)
        threads[current_id].state = RUNNING;
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
            threads[i].ptr            = func;
            threads[i].state          = INIT;
            threads[i].end_flag       = false;
            threads[i].args           = args;
            threads[i].stack_pointer  = stack_pointer; //TO DO: stack to id
            threads[i].priority       = priority;
            errno                     = 0;

            allocate_stack(stack_pointer, i);
            thread_num++;
            break;
        }
    }
    return errno;

}



bool is_end()
{
    return threads[current_id].end_flag;
}

void set_end(const bool val)
{
    threads[current_id].end_flag = val;
}

void thread_manager()
{

    init_stack();

    for(int i = 0, j = 0; j< 50;  i = (++i % (thread_num ) ), j++)
    {
        if(threads[i].state != TERMINATE)
        {
            current_id = i;
            threads[i].ptr(threads[i].args);
        }
        else
        {
            threads[i].ptr = 0;
            //TO DO: mem delete
        }


    }
    thread_num = 0;
}
