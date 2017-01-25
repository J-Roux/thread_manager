#include "thread_manager.h"

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
    uint8_t max_call_level;
    uint8_t current_call_level;
} thread_context;




static uint8_t pointer = 0;

static thread_context threads[MAX_THREAD_COUNT];

static uint8_t current_id;

void terminate_thread()
{
    threads[get_id()].state = END;
}


uint8_t get_id()
{
    return current_id;
}

static thread_state get_thread_state()
{
    return threads[current_id].state;
}

static void set_thread_state(const thread_state state)
{
    threads[current_id].state = state;
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
    if(get_thread_state() == NOT_INIT)
        set_thread_state(RUNNING);
    if( is_next_stack_frame_exist(size))
        load(ptr, size);
}


void clear_thread_table()
{
    pointer = 0;
}


void create_thread(const func_ptr func)
{
    if(pointer < MAX_THREAD_COUNT)
    {
        threads[pointer].ptr = func;
        threads[pointer].state = NOT_INIT;
        threads[pointer].current_call_level = 0;
        threads[pointer].max_call_level = 0;
        pointer++;
    }
}

static bool end[MAX_THREAD_COUNT];

bool is_end()
{
    return end[current_id];
}

void set_end(const bool val)
{
    end[current_id] = val;
}

void thread_manager()
{
    for (int i = 0; i < MAX_THREAD_COUNT; end[i]= false, i++);
    for(int i = 0, j =0; j < 40; i = (++i % MAX_THREAD_COUNT), j++)
    {
        current_id = i;
        if(threads[i].state != END)
            threads[i].ptr();
    }
}
