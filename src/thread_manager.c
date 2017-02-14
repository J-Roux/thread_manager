#include "thread_manager.h"
#include "clock.h"


typedef enum
{
        TERMINATE,
        INIT,
        WAIT,
        RUNNING
} thread_state;





typedef struct
{
        uint8_t             state       : 3;
        uint8_t             priority    : 4;
        bool                end_flag    : 1;
        uint8_t             errno          ;
        clock_t             start_time     ;
        time_interval       interval       ;
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




void start_timer(uint16_t sec, uint16_t usec, uint16_t micro_sec)
{
        if(threads[get_id()].info.state != WAIT)
        {
                time_interval interval = { sec, usec, micro_sec };
                threads[get_id()].info.interval           = interval;
                threads[get_id()].info.start_time         = clock();
                threads[get_id()].info.state              = WAIT;
        }
}


const uint8_t get_id()
{
        return current_id;
}


void save_context(const uint8_t* ptr, const uint8_t size)
{
        push(ptr, size);
}

void _yield(uint8_t* context, uint8_t size, int32_t *pc, int32_t line)
{
        if(*pc != 0)
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
                if(load(ptr, size) == STACK_OVERFLOW)
                        threads[current_id].info.errno = STACK_OVERFLOW;
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
                        time_interval zero = {0};
                        threads[i].info.priority           = priority;
                        threads[i].info.state              = INIT;
                        threads[i].info.end_flag           = false;
                        threads[i].info.start_time         = 0;
                        threads[i].info.interval           = zero;
                        threads[i].ptr                     = func;
                        threads[i].args                    = args;
                        threads[i].stack_pointer           = stack_pointer;
                        errno                              = 0;
                        allocate_stack(stack_pointer, i);
                        if(thread_num != MAX_THREAD_COUNT)
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
        for(int i = 0; ; )
        {

                switch(threads[i].info.state)
                {
                        case WAIT:
                        {
                                clock_t end = clock();
                                time_interval interval = get_time_interval(&(threads[i].info.start_time), &end);
                                if(greater_interval(&interval, &(threads[i].info.interval)))
                                {
                                        time_interval zero                 = {0};
                                        threads[i].info.state              = RUNNING;
                                        threads[i].info.start_time         = 0;
                                        threads[i].info.interval           = zero;
                                }
                                else
                                        break;
                        }
                        case INIT:
                        case RUNNING:
                        {
                                current_id = i;
                                threads[i].ptr(threads[i].args);
                                break;
                        }

                        case TERMINATE:
                        {
                                threads[i].ptr = 0;
                                dead_thread++;
                                break;
                        }
                }

                if(dead_thread == thread_num )
                {
                        thread_num = 0;
                        break;
                }
                if(i == thread_num - 1)
                        dead_thread = 0;
                i++;
                i = ( i % (thread_num ));
        }
        thread_num = 0;
}
