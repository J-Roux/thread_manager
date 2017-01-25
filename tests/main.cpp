#include "../src/thread_manager.h"
#include <iostream>
#include <functional>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <type_traits>
#include <vector>
#include <string>
#include <functional>




std::vector<std::string> message_queue;

void f1()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD
       THIS.a = 7;
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
    END_THREAD;
}

void f2()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD
        THIS.a = 5;
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
    END_THREAD;
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
    clear_thread_table();
}

void thread1()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 1;
    YIELD;
       message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
    END_THREAD;
}

void nested_function()
{
    DECLARE_AREA;
            uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD
        THIS.a = 3;
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
        set_end(true);
        pop(sizeof(_thread_context)); // pop only if yield
    }
}

void thread2()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD;
        THIS.a = 2;
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );


    CALL( nested_function() );


    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );

   END_THREAD;
}


TEST(thread_manager, call_func_into_thread)
{
    create_thread(&thread1);
    create_thread(&thread2);
    thread_manager();
    message_queue.push_back("end kernel");
    std::vector<std::string> expected_message_queue = {
        "thread1 1",
        "thread2 2",
        "thread1 1",
        "nested_function 3",
        "thread1 1",
        "nested_function 3",
        "thread1 1",
        "thread2 2",
        "end kernel"
    };
    EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));
    message_queue.clear();
    clear_thread_table();
}


