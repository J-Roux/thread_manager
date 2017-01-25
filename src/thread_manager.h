#ifndef _THREAD_MANAGER
#define _THREAD_MANAGER

#include "stack.h"
#include "thread_manager_config.h"
#include <stdbool.h>
typedef void(*func_ptr)();

#define THIS _thread_context
#define DECLARE_AREA struct { \
    uint32_t pc \

#define END_DECLARE_AREA } _thread_context;\
_thread_context.pc = 0;\
load_context((uint8_t*)&_thread_context, sizeof(_thread_context));\

#define BEGIN_THREAD  switch(_thread_context.pc) { case 0:


#define END_THREAD   set_end(true); pop(sizeof(_thread_context)); terminate_thread();  }

#define YIELD  case __LINE__: {  \
if(THIS.pc > 0)     \
    pop(sizeof(_thread_context));  \
_thread_context.pc = __LINE__ + 1;             \
save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); \
reset(); \
break;  \
}       \
case __LINE__ + 1: \



#define _YIELD  case __LINE__: {_thread_context.pc = __LINE__ + 1;  \
               reset(); \
               if(!is_next_stack_frame_exist(sizeof(_thread_context))) pop(sizeof(_thread_context));\
               save_context((uint8_t*)&_thread_context, sizeof(_thread_context));  \
               break; \
               }\
               case __LINE__ + 1: \

#define CALL(CALLABLE_EXPR)         case  __LINE__: \
if(THIS.pc > 0)                     \
{ \
    pop(sizeof(_thread_context));   \
    _thread_context.pc = __LINE__ + 1; \
    save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); \
}                                                                       \
case __LINE__ + 1: CALLABLE_EXPR;     \
if(!is_end())     \
{    \
    break; \
}           \
else        \
{           \
    set_end(false); \
    load_context((uint8_t*)&_thread_context, sizeof(_thread_context));  \
    THIS.pc = __LINE__ + 2; \
}   \
case __LINE__ + 2:  \




#ifdef __cplusplus
extern "C" {
#endif

uint8_t get_id();
void create_thread(const func_ptr func);
void load_context(uint8_t* ptr,const uint8_t size);
void save_context(const uint8_t* ptr,const uint8_t size);
void thread_manager();
void terminate_thread();
bool is_end();
void set_end(const bool val);
void inc_call_level();
void dec_call_level();
void end_func();
bool is_this_frame(const uint8_t size);
void clear_thread_table();

#ifdef __cplusplus
}
#endif
#endif
