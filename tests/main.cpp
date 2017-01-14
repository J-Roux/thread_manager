#include "../src/thread_manager.h"
#include <iostream>
#include <functional>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <type_traits>
#include <vector>
#include <string>




REGISTER(f1);
REGISTER(f2);




std::vector<std::string> message_queue;

void f1()
{
   YIELD(_f1);
   message_queue.push_back("f1 one");
   YIELD(_f1);
   message_queue.push_back("f1 two");
   END_THREAD;
}

void f2()
{
   YIELD(_f2);
   message_queue.push_back("f2 one");
   YIELD(_f2);
   message_queue.push_back("f2 two");
   END_THREAD;
}


TEST(thread_manager, normal_workflow)
{
    jmp_buf_ptr constexts[2] = { &_f1, &_f2};
    Func  func_array[2] = { &f1, &f2 };
    kernel(constexts,func_array, 2);
    message_queue.push_back("end kernel");
    std::vector<std::string> expected_message_queue = {
        "f1 one",
        "f2 one",
        "f1 two",
        "f2 two",
        "end kernel"
    };

    EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));


}
