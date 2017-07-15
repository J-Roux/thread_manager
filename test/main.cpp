#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/threadManager.hpp"
#include <vector>


void Wait(double delta)
{
        clock_t expire = clock() + delta * CLOCKS_PER_SEC;
        while (clock() < expire);
}

TEST(Casting, timeToClock)
{
    ASSERT_EQ(CLOCKS_PER_SEC, timeToClock(1, 0, 0));
}


TEST(Timer, msec)
{
    auto start = clock();
    Wait(0.5);
    auto end = clock();
    ASSERT_EQ(end - start, timeToClock(0, 500, 0));
}


TEST(Timer, sec)
{
    auto start = clock();
    Wait(1);
    auto end = clock();
    ASSERT_EQ(end - start, timeToClock(1, 0, 0));
}




std::vector<std::string> messageQueue;

class ThreadOne : public IThread
{
    uint8_t i;
public:
    ThreadOne(IStack<uint32_t> *stack) : i(0), IThread(stack) {}
    virtual void operator ()()
    {
        BEGIN_THREAD;
        messageQueue.push_back(std::to_string(i));
        YIELD;
        messageQueue.push_back(std::to_string(i));
        END_THREAD;
    }
    virtual ~ThreadOne() {}
};

class WatchDog : public IThread
{
public:
    WatchDog(IStack<uint32_t> *stack) : IThread(stack) {}
    virtual void operator ()()
    {
        BEGIN_THREAD;
        messageQueue.push_back("watchdog");
        YIELD;
        messageQueue.push_back("watchdog");
        END_THREAD;
    }
    virtual ~WatchDog() {}
};

TEST(ThreadManager, NormalWorkflow)
{
    std::vector<std::string> expectedMessageQueue{
        "0",
        "watchdog",
        "0",
        "watchdog"
    };
    ThreadOne thread1(NULL);
    WatchDog watchDog(NULL);
    ThreadManager<2> manager;
    manager.CreateThread(&thread1);
    manager.CreateThread(&watchDog);
    manager.loop();
    EXPECT_THAT(expectedMessageQueue, ::testing::ContainerEq(messageQueue));
    messageQueue.clear();
}


class SleepingThread : public IThread
{
    uint8_t i;
public:
    SleepingThread(IStack<uint32_t> *stack) : i(6), IThread(stack) {}
    virtual void operator ()()
    {
        BEGIN_THREAD;
        for(; i != 0; i--)
        {
            messageQueue.push_back("SleepingThread");
            WAIT_FOR(0, 500, 0);
        }
        END_THREAD;
    }
    virtual ~SleepingThread() {}
};


class WaitThread : public IThread
{
    uint8_t i;
public:
    WaitThread(IStack<uint32_t> *stack) : i(3), IThread(stack) {}
    virtual void operator ()()
    {
        BEGIN_THREAD;
        for(; i != 0; i--)
        {
            messageQueue.push_back("WaitThread");
            WAIT_FOR(1, 0, 0);
        }
        END_THREAD;
    }
    virtual ~WaitThread() {}
};


TEST(ThreadManager, Wait)
{
    std::vector<std::string> expectedMessageQueue{
        "WaitThread",
        "SleepingThread",
        "SleepingThread",
        "WaitThread",
        "SleepingThread",
        "SleepingThread",
        "WaitThread",
        "SleepingThread",
        "SleepingThread"
    };
    SleepingThread thread1(NULL);
    WaitThread watchDog(NULL);
    ThreadManager<2> manager;
    manager.CreateThread(&watchDog);
    manager.CreateThread(&thread1);
    manager.loop();
    EXPECT_THAT(expectedMessageQueue, ::testing::ContainerEq(messageQueue));
    messageQueue.clear();
}


//void f1(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        END_DECLARE_AREA;
//        BEGIN_THREAD
//                        THIS.a = 7;
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        END_THREAD;
//}

//void f2(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        END_DECLARE_AREA;
//        BEGIN_THREAD
//                        THIS.a = 5;
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        END_THREAD;
//}



//TEST(tm_thread_manager, normal_workflow)
//{
//        uint8_t stack_one[STACK_SIZE];
//        uint8_t stack_two[STACK_SIZE];
//        tm_create_thread(&f1, 0, stack_one, thread_priotity_idle);
//        tm_create_thread(&f2, 0, stack_two, thread_priotity_idle);
//        tm_thread_manager();
//        message_queue.push_back("end kernel");
//        std::vector<std::string> expected_message_queue = {
//                "f1 7",
//                "f2 5",
//                "f1 7",
//                "f2 5",
//                "end kernel"
//        };
//        EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));
//        message_queue.clear();
//}

//void thread1(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        END_DECLARE_AREA;
//        BEGIN_THREAD;
//        THIS.a = 1;
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        END_THREAD;
//}

//void nested_function()
//{
//        DECLARE_AREA;
//        uint8_t a;
//        END_DECLARE_AREA;
//        BEGIN_THREAD
//        THIS.a = 3;
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        END;
//}

//void thread2(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        END_DECLARE_AREA;
//        BEGIN_THREAD;
//        THIS.a = 2;
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        CALL( nested_function());

//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        END_THREAD;
//}


//TEST(tm_thread_manager, call_func_into_thread)
//{
//        uint8_t stack_one[STACK_SIZE];
//        uint8_t stack_two[STACK_SIZE];
//        tm_create_thread(&thread1, 0, stack_one, thread_priotity_idle);
//        tm_create_thread(&thread2, 0, stack_two, thread_priotity_idle);
//        tm_thread_manager();
//        message_queue.push_back("end kernel");
//        std::vector<std::string> expected_message_queue = {
//                "thread1 1",
//                "thread2 2",
//                "thread1 1",
//                "nested_function 3",
//                "thread1 1",
//                "nested_function 3",
//                "thread1 1",
//                "thread2 2",
//                "end kernel"
//        };
//        EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));
//        message_queue.clear();
//}


//uint8_t stack_one[STACK_SIZE];
//uint8_t stack_two[STACK_SIZE];
//uint8_t stack_three[STACK_SIZE];


//void thread_child(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        END_DECLARE_AREA;
//        BEGIN_THREAD;
//        THIS.a = 3;
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        END_THREAD;
//}


//void thread_parent(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        END_DECLARE_AREA;
//        BEGIN_THREAD
//                        THIS.a = 2;
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        tm_create_thread(&thread_child, 0, stack_three, thread_priotity_idle);
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        END_THREAD;
//}



//TEST(tm_thread_manager, create_thread_into_thread)
//{
//        tm_create_thread(&thread1, 0, stack_one, thread_priotity_idle);
//        tm_create_thread(&thread_parent, 0, stack_two, thread_priotity_idle);
//        tm_thread_manager();
//        message_queue.push_back("end kernel");
//        std::vector<std::string> expected_message_queue = {
//                "thread1 1",
//                "thread_parent 2",
//                "thread1 1",
//                "thread_parent 2",
//                "thread_child 3",
//                "thread1 1",
//                "thread_parent 2",
//                "thread_child 3",
//                "thread1 1",
//                "thread_parent 2",
//                "thread_child 3",
//                "thread_child 3",
//                "end kernel"
//        };
//        EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));
//        message_queue.clear();
//}

//void f3(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        bool f = false;
//        END_DECLARE_AREA;
//        BEGIN_THREAD
//                        THIS.a = 7;
//        if(THIS.f)
//        {
//                YIELD;
//                message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        }
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        END_THREAD;
//}

//void f4(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        END_DECLARE_AREA;
//        BEGIN_THREAD
//                        THIS.a = 5;
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        YIELD;
//        message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        END_THREAD;
//}

//TEST(tm_thread_manager, if_statement)
//{
//        tm_create_thread(&f3, 0, stack_one, thread_priotity_idle);
//        tm_create_thread(&f4, 0, stack_two, thread_priotity_idle);
//        tm_thread_manager();
//        message_queue.push_back("end kernel");
//        std::vector<std::string> expected_message_queue = {
//                "f3 7",
//                "f4 5",
//                "f4 5",
//                "end kernel"
//        };
//        EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));
//        message_queue.clear();
//}

//void f5(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        uint8_t i;
//        END_DECLARE_AREA;
//        BEGIN_THREAD;
//        THIS.a = 1;
//        for(THIS.i = 0; THIS.i < 4; THIS.i++)
//        {
//                YIELD;
//                message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        }
//        END_THREAD;
//}

//void f6(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        uint8_t i;
//        END_DECLARE_AREA;
//        BEGIN_THREAD;
//        THIS.a = 2;
//        for(THIS.i = 0; THIS.i < 4; THIS.i++)
//        {
//                YIELD;
//                message_queue.push_back(std::string(__FUNCTION__) + std::string(" ")+ std::to_string(THIS.a) );
//        }
//        END_THREAD;
//}




//TEST(tm_thread_manager, for_statement)
//{
//        tm_create_thread(&f5, 0, stack_one, thread_priotity_idle);
//        tm_create_thread(&f6, 0, stack_two, thread_priotity_idle);
//        tm_thread_manager();
//        message_queue.push_back("end kernel");
//        std::vector<std::string> expected_message_queue = {
//                "f5 1",
//                "f6 2",
//                "f5 1",
//                "f6 2",
//                "f5 1",
//                "f6 2",
//                "f5 1",
//                "f6 2",
//                "end kernel"
//        };
//        EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));
//        message_queue.clear();
//}





//void Wait(double delta)
//{
//        clock_t expire = clock() + delta * CLOCKS_PER_SEC;
//        while (clock() < expire) {
//        }
//}




//void wait_thread(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        uint8_t i;
//        END_DECLARE_AREA;
//        BEGIN_THREAD;
//        for( THIS.i = 0; THIS.i < 3; THIS.i++)
//        {
//                message_queue.push_back(std::string(__FUNCTION__) );
//                WAIT_FOR(0, 1, 0);
//        }
//        END_THREAD;
//}



//void sleep_thread(uint8_t * args)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        uint8_t i;
//        END_DECLARE_AREA;
//        BEGIN_THREAD;
//        for(THIS.i = 0; THIS.i < 6; THIS.i++)
//        {
//                message_queue.push_back(std::string(__FUNCTION__) );
//                Wait(0.0005);
//                YIELD;
//        }
//        END_THREAD;
//}




//TEST(tm_thread_manager, wait)
//{
//        uint8_t stack_one[STACK_SIZE];
//        uint8_t stack_two[STACK_SIZE - 10];
//        tm_create_thread(&wait_thread, 0, stack_one, thread_priotity_idle);
//        tm_create_thread(&sleep_thread, 0, stack_two, thread_priotity_idle);
//        tm_thread_manager();
//        message_queue.push_back("end kernel");
//        std::vector<std::string> expected_message_queue = {
//                "wait_thread",
//                "sleep_thread",
//                "sleep_thread",
//                "wait_thread",
//                "sleep_thread",
//                "sleep_thread",
//                "wait_thread",
//                "sleep_thread",
//                "sleep_thread",
//                "end kernel"
//        };
//        EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));
//        message_queue.clear();
//}



//void f10(uint8_t * ptr)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        uint8_t i;
//        int cnt;
//        END_DECLARE_AREA;
//        BEGIN_THREAD;
//        THIS.cnt = 0;
//        for( THIS.i = 0; THIS.i < 2; THIS.i++)
//        {
//                message_queue.push_back(std::string(__FUNCTION__) );
//                WAIT_FOR(0, 400, 0);
//        }
//        END_THREAD;
//}

//void f20(uint8_t * ptr)
//{
//        DECLARE_AREA;
//        uint8_t a;
//        uint8_t i;
//        int cnt;
//        END_DECLARE_AREA;
//        BEGIN_THREAD;
//        THIS.cnt = 0;
//        for(THIS.i = 0; THIS.i < 5; THIS.i++)
//        {
//                tm_create_thread(&f10, 0, stack_two, thread_priotity_idle);
//                message_queue.push_back(std::string(__FUNCTION__) );
//                WAIT_FOR(1, 0, 0);
//        }
//        END_THREAD;
//}


//TEST(tm_thread_manager, korevko)
//{
//        uint8_t stack_one[STACK_SIZE];

//        tm_create_thread(&f20, 0, stack_one, thread_priotity_idle);
//        tm_thread_manager();
//        message_queue.push_back("end kernel");
//        std::vector<std::string> expected_message_queue = {
//                "f20",
//                "f10",
//                "f10",
//                "f20",
//                "f10",
//                "f10",
//                "f20",
//                "f10",
//                "f10",
//                "f20",
//                "f10",
//                "f10",
//                "f20",
//                "f10",
//                "f10",
//                "end kernel"
//        };
//        EXPECT_THAT(expected_message_queue, ::testing::ContainerEq(message_queue));
//        message_queue.clear();
//}

