#ifndef _STACK_H
#define _STACK_H
#include <stdint.h>

typedef int16_t ptr_size;

typedef enum
{
    SUCCESS,
    STACK_OVERFLOW
} RESULT;

#define STACK_SIZE 124

#define STACK_START_ADDRESS -1
#ifdef __cplusplus
extern "C" {
#endif

RESULT push(uint8_t *ptr, ptr_size size);
RESULT pop(uint8_t *ptr, ptr_size size);



#ifdef __cplusplus
}
#endif
#endif
