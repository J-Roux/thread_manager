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

thread_state get_thread_state()
{
    return threads[current_id].state;
}

void set_thread_state(thread_state state)
{
    threads[current_id].state = state;
}


void save_context(uint8_t* ptr, uint8_t size)
{
    push(ptr, size);
}

void load_context(uint8_t* ptr, uint8_t size)
{
    if(get_thread_state() != NOT_INIT)
    {
        pop(ptr, size);
    }
    else
        set_thread_state(RUNNING);
}


void create_thread(func_ptr func)
{
    if(pointer < MAX_THREAD_COUNT)
    {
        threads[pointer].ptr = func;
        threads[pointer].state = NOT_INIT;
        pointer++;
    }
}

bool end[MAX_THREAD_COUNT];

bool is_end()
{
    return end[current_id];
}

void set_end(bool val)
{
    end[current_id] = val;
}

void thread_manager()
{
    for (int i = 0; i < MAX_THREAD_COUNT; end[i]= false, i++);
    for(int i = 0, j =0; j < 6; i = (++i % MAX_THREAD_COUNT), j++)
    {
        current_id = i;
        if(threads[i].state != END)
            threads[i].ptr();
    }
}
