#ifndef _THREAD_MANAGER
#define _THREAD_MANAGER

#include "thread_manager_config.h"
#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>

typedef void(*func_ptr)(uint8_t id, int argc, void* argv);

typedef jmp_buf * jmp_buf_ptr;

#define _THREAD(NAME) void NAME(uint8_t id, int argc, void* argv) \
{ \
    uint8_t _id = id; \
    static jmp_buf local;  \
    add_context(&local, id);


#ifdef __cplusplus
extern "C" {
#endif

jmp_buf_ptr get_kernel_context();

uint8_t create_thread(func_ptr ptr, uint8_t argc, void* argv);

void add_context(jmp_buf_ptr context, uint8_t id);

void thread_manager();



int8_t set_context(uint8_t id);

jmp_buf_ptr get_context(uint8_t id);

void end_thread(uint8_t id);

#define YIELD     if(setjmp(local) == 0) \
                    longjmp(*get_kernel_context(), __COUNTER__)

#define END_THREAD end_thread(id)
#ifdef __cplusplus
}
#endif


#endif
