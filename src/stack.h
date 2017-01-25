#ifndef _STACK_H
#define _STACK_H
#include <stdint.h>
#include <stdbool.h>
#include "thread_manager.h"
typedef int16_t ptr_size;

typedef enum
{
    SUCCESS,
    STACK_OVERFLOW
} RESULT;

#define STACK_SIZE 32

#define STACK_START_ADDRESS -1
#ifdef __cplusplus
extern "C" {
#endif


RESULT load(uint8_t* ptr, const ptr_size size);
RESULT push(const uint8_t *ptr, const ptr_size size);
RESULT pop(const ptr_size size);
void reset();
bool is_next_stack_frame_exist(const uint8_t size);
void init_stack();
void allocate_stack(uint8_t * ptr, uint8_t stack_num);


#ifdef __cplusplus
}
#endif
#endif
