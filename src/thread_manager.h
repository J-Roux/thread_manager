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




#ifdef __cplusplus
extern "C" {
#endif


void tm_yield(uint8_t* context, uint8_t size, int32_t* pc, int32_t line);

const uint8_t tm_get_id();

int8_t tm_create_thread(const func_ptr func, uint8_t* args,  uint8_t* stack_pointer, thread_priority priority);

void tm_load_context(uint8_t* ptr,const uint8_t size);

void tm_save_context(const uint8_t* ptr,const uint8_t size);

void tm_thread_manager();

void tm_terminate_thread(uint32_t size);

void tm_start_timer(uint16_t sec, uint16_t usec, uint16_t micro_sec);

const bool tm_is_exception_thrown();

bool tm_is_end();

void tm_set_end(const bool val);

void tm_save_state(uint8_t* context, uint16_t size);

#ifdef __cplusplus
}
#endif






#define THIS              _thread_context
#define DECLARE_AREA      struct \
                          { \
                                int32_t pc \

#define END_DECLARE_AREA  } _thread_context;\
                          _thread_context.pc = 0;\
                          tm_load_context((uint8_t*)&_thread_context, sizeof(_thread_context));\
//                          if(is_exception_thrown()) \
//                                goto end_function; \

#define BEGIN_THREAD      switch( _thread_context.pc) { case 0:{}

#define BEGIN             switch( _thread_context.pc) { case 0:{}


#define END               tm_set_end(true); \
                          if(THIS.pc != 0)\
                               pop(sizeof(_thread_context)); \
                          }   \
                          end_function:{}\

#define END_THREAD        tm_terminate_thread(sizeof(_thread_context));\
                          } end_function: {} \

#define YIELD             case __LINE__:   \
                          tm_yield((uint8_t*)&_thread_context, sizeof(_thread_context), &(_thread_context.pc),  -__LINE__); \
                          goto end_function;  \
                                \
                          case -__LINE__: {} \



#define WAIT_FOR(SEC, USEC, MICRO_SEC) tm_start_timer(SEC, USEC, MICRO_SEC); YIELD;



#define CALL(CALLABLE_EXPR)         case  __LINE__:\
                                    { \
                                        if(THIS.pc != 0)                     \
                                        { \
                                                _thread_context.pc = - __LINE__; \
                                                tm_save_state((uint8_t*)&_thread_context, sizeof(_thread_context));\
                                        } \
                                    } \
                                    case -__LINE__ :{} CALLABLE_EXPR;     \
                                    if(!tm_is_end())     \
                                    {    \
                                        break; \
                                    }           \
                                    else        \
                                    {           \
                                        tm_set_end(false); \
                                        tm_load_context((uint8_t*)&_thread_context, sizeof(_thread_context));  \
                                        THIS.pc = __LINE__ + 1; \
                                    }   \
                                    case __LINE__ + 1: {} \



#endif
