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
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD
       _thread_context.a = 7;
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(_thread_context.a) );
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(_thread_context.a) );
    END_THREAD;
}

void f2()
{
    DECLARE_AREA;
        uint8_t a;
    END_DECLARE_AREA;
    BEGIN_THREAD
       _thread_context.a = 5;
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(_thread_context.a) );
    YIELD;
        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(_thread_context.a) );
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

}
