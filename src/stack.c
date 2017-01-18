#include "stack.h"
#include "thread_manager_config.h"
#include <string.h>
static uint8_t data[MAX_THREAD_COUNT][STACK_SIZE];
static ptr_size pointer[MAX_THREAD_COUNT] = { STACK_START_ADDRESS, STACK_START_ADDRESS };
static ptr_size context_pointer[MAX_THREAD_COUNT] = { STACK_START_ADDRESS, STACK_START_ADDRESS };
void reset() { pointer[get_id()] = STACK_START_ADDRESS; }

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

RESULT pop(uint8_t *ptr,const ptr_size size)
{
  RESULT result = range_check( size, POP);
  if(result == SUCCESS)
  {
      pointer[get_id()] -= size - 1;
      memcpy(ptr, data[get_id()] + pointer[get_id()], size);
      (pointer[get_id()])--;
  }
  return result;
}




