#ifndef _THREAD_MANAGER
#define _THREAD_MANAGER

#include "stack.h"
#include "thread_manager_config.h"
typedef void(*func_ptr)();


#ifdef __cplusplus
extern "C" {
#endif

uint8_t get_id();
void create_thread(func_ptr func);
void load_context(uint8_t* ptr, uint8_t size);
void save_context(uint8_t* ptr, uint8_t size);
void thread_manager();

#ifdef __cplusplus
}
#endif
#endif
