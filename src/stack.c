#include "stack.h"

static uint8_t data[STACK_SIZE];
static ptr_size pointer = STACK_START_ADDRESS;

ptr_size get_pointer() { return pointer;}
void reset() { pointer = STACK_START_ADDRESS; }
uint8_t* get_head(uint8_t shift )
{
    if(pointer >= 0)
    {
        return data + pointer - shift + 1;
    }
    else
    {
        return 0;
    }
}

typedef enum
{
    PUSH,
    POP
} COMPARE_TYPE;

RESULT range_check(ptr_size size, COMPARE_TYPE type)
{
    RESULT result = SUCCESS;
    if(type == PUSH)
    {
        if( pointer + size > STACK_SIZE)
            result = STACK_OVERFLOW;
    }
    else
    {
        if( pointer - size < STACK_START_ADDRESS)
            result = STACK_OVERFLOW;
    }
    return result;
}


RESULT push(uint8_t *ptr, ptr_size size)
{
  RESULT result = range_check(size, PUSH);
  if(result == SUCCESS)
  {
    memcpy(data + ++pointer, ptr, size);
    pointer += size - 1;
  }
  return result;
}

RESULT pop(uint8_t *ptr, ptr_size size)
{
  RESULT result = range_check( size, POP);
  if(result == SUCCESS)
  {
      pointer -= size - 1;
      memcpy(ptr, data + pointer--, size);
  }
  return result;
}




