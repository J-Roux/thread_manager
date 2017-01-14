#ifndef _THREAD_MANAGER_HEADER
#define _THREAD_MANAGER


#include <setjmp.h>

typedef void(*Func)();
typedef jmp_buf * jmp_buf_ptr;

#define REGISTER(FUNC) jmp_buf _##FUNC; void FUNC()



#define YIELD(context)    if(setjmp(context) == 0) \
                            longjmp(*get_kernel_context(), __COUNTER__); \

#define END_THREAD    end_thread(); \
                      longjmp(*get_kernel_context(), __COUNTER__) \


#ifdef __cplusplus
extern "C" {
#endif

void kernel(jmp_buf_ptr* contexts, Func * funcs, int len);

void end_thread();

jmp_buf_ptr get_kernel_context();

#ifdef __cplusplus
}
#endif


#endif
