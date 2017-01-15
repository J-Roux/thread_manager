#include "../src/thread_manager.h"
#include <iostream>
#include <functional>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <type_traits>
#include <vector>
#include <string>





std::vector<std::string> message_queue;

_THREAD(f1)
    DECLARE
    END_DECLARE
    YIELD;
    message_queue.push_back("f1 one");
    YIELD;
    message_queue.push_back("f1 two");
    END_THREAD;
}

_THREAD(f2)
    DECLARE
    END_DECLARE
    YIELD;
    message_queue.push_back("f2 one");
    YIELD;
    message_queue.push_back("f2 two");
    END_THREAD;
}




TEST(thread_manager, normal_workflow)
{
    create_thread(f1, 0, 0);
    create_thread(f2, 0, 0);
    thread_manager();
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
