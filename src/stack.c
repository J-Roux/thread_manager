#include "stack.h"
#include "thread_manager_config.h"
#include <string.h>
static uint8_t *data[MAX_THREAD_COUNT];
static ptr_size pointer[MAX_THREAD_COUNT];
static ptr_size context_pointer[MAX_THREAD_COUNT];
void reset() { context_pointer[get_id()] = STACK_START_ADDRESS; }

typedef enum
{
    PUSH,
    POP
} COMPARE_TYPE;

RESULT range_check(const ptr_size size, const COMPARE_TYPE type)
{
    RESULT result = SUCCESS;
    if(type == PUSH)
    {
        if( pointer[get_id()] + size > STACK_SIZE)
            result = STACK_OVERFLOW;
    }
    else
    {
        if( pointer[get_id()] - size < STACK_START_ADDRESS)
            result = STACK_OVERFLOW;
    }
    return result;
}


RESULT push(const uint8_t *ptr, const ptr_size size)
{
  RESULT result = range_check(size, PUSH);
  if(result == SUCCESS)
  {
    ++(pointer[get_id()]);
    memcpy(data[get_id()] + pointer[get_id()], ptr, size);
    pointer[get_id()] += size - 1;

  }
  return result;
}


RESULT pop(const ptr_size size)
{
        pointer[get_id()] -= size - 1;
        (pointer[get_id()])--;
}

RESULT load(uint8_t* ptr, const ptr_size size)
{
    RESULT result = range_check( size, POP);
    if(result == SUCCESS)
    {
        ++(context_pointer[get_id()]);
        memcpy(ptr, data[get_id()] + context_pointer[get_id()], size);
        context_pointer[get_id()] += size - 1;
    }
    return result;
}

bool is_next_stack_frame_exist(const uint8_t size)
{
    return context_pointer[get_id()] + size <= pointer[get_id()];
}

void init_stack()
{
    for(uint8_t i = 0; i < MAX_THREAD_COUNT; i++)
    {
        pointer[i] = STACK_START_ADDRESS;
        context_pointer[i] = STACK_START_ADDRESS;
    }
}

void allocate_stack(uint8_t * ptr, uint8_t stack_num)
{
    data[stack_num] = ptr;
}
