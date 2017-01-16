#include "../src/thread_manager.h"
#include <iostream>
#include <functional>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <type_traits>
#include <vector>
#include <string>





std::vector<std::string> message_queue;

void f1()
{
    struct {
        uint32_t pc;
        uint8_t a;

    } _thread_context;
    _thread_context.pc = 0;
    load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
    switch (_thread_context.pc)
    {
    case 0:
    {
        _thread_context.a = 7;
    }
    case __LINE__: _thread_context.pc = __LINE__ + 1; save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(_thread_context.a) );
    }
    case __LINE__: _thread_context.pc = __LINE__ + 1; save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(_thread_context.a) );
    }
    }
}

void f2()
{

    struct {
        uint32_t pc;
        uint8_t a;

    } _thread_context;
    _thread_context.pc = 0;
    load_context((uint8_t*)&_thread_context, sizeof(_thread_context));
    switch (_thread_context.pc)
    {
    case 0:
    {
        _thread_context.a = 5;

    }
    case __LINE__: _thread_context.pc = __LINE__ + 1; save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(_thread_context.a) );

    }
    case __LINE__: _thread_context.pc = __LINE__ + 1; save_context((uint8_t*)&_thread_context, sizeof(_thread_context)); return;
    case __LINE__:
    {
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(_thread_context.a) );
    }
    }
}



TEST(thread_manager, normal_workflow)
{
    create_thread(&f1);
    create_thread(&f2);
    thread_manager();
    message_queue.push_back("end kernel");
    std::vector<std::string> expected_message_queue = {
        "f1 7",
        "f2 5",
        "f1 7",
        "f2 5",
        "end kernel"
    };

    EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));
    message_queue.clear();

}
