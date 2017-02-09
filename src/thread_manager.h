#ifndef _THREAD_MANAGER
#define _THREAD_MANAGER

#include "stack.h"
#include "thread_manager_config.h"
#include <stdbool.h>
typedef void(*func_ptr)(uint8_t* argv);

typedef enum
{
    thread_priotity_idle

} thread_priority;




#define THIS _thread_context
#define DECLARE_AREA struct { \
    uint32_t pc \

#define END_DECLARE_AREA } _thread_context;\
_thread_context.pc = 0;\
load_context((uint8_t*)&_thread_context, sizeof(_thread_context));\

#define BEGIN_THREAD  switch(_thread_context.pc) { case 0:{}

#define BEGIN  switch(_thread_context.pc) { case 0:{}


#define END        set_end(true); \
if(THIS.pc > 0)                     \
    pop(sizeof(_thread_context)); \
}   \
end_function: \
  // TO DO : return val

#define END_THREAD   set_end(true); pop(sizeof(_thread_context)); terminate_thread();  } end_function: {}

#define YIELD  case __COUNTER__ + 1:   \
_yield((uint8_t*)&_thread_context, sizeof(_thread_context), &(_thread_context.pc), __COUNTER__ + 2); \
goto end_function;  \
      \
case __COUNTER__ + 1: {} \



#define WAIT_FOR(SEC, USEC, MICRO_SEC) start_timer(SEC, USEC, MICRO_SEC); YIELD;



#define CALL(CALLABLE_EXPR)         case  __COUNTER__ + 1:{ \
if(THIS.pc > 0)                     \
{ \
    pop(sizeof(_thread_context));   \
    _thread_context.pc = __COUNTER__ + 1; \
    save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); \
} \
} \
case __COUNTER__ :{} CALLABLE_EXPR;     \
if(!is_end())     \
{    \
    break; \
}           \
else        \
{           \
    set_end(false); \
    load_context((uint8_t*)&_thread_context, sizeof(_thread_context));  \
    THIS.pc = __COUNTER__ + 2; \
}   \
case __COUNTER__ + 1: {} \



#ifdef __cplusplus
extern "C" {
#endif
void _yield(uint8_t* context, uint8_t size, uint32_t *pc, uint32_t line);
const uint8_t get_id();
int create_thread(const func_ptr func, uint8_t* args,  uint8_t* stack_pointer, thread_priority priority);
void load_context(uint8_t* ptr,const uint8_t size);
void save_context(const uint8_t* ptr,const uint8_t size);
void thread_manager();
void terminate_thread();
void start_timer(uint16_t sec, uint16_t usec, uint16_t micro_sec);
bool is_end();
void set_end(const bool val);


#ifdef __cplusplus
}
#endif
#endif
