project(ThreadManager)
cmake_minimum_required(VERSION 2.8)
option(test "Build all tests." ON)

file(GLOB SRC_LIST ./src/* )
file(GLOB MAIN ./*.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${MAIN})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 98)

if (test)
 include(ExternalProject)

 set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

 ExternalProject_Add(googletest
     GIT_REPOSITORY https://github.com/google/googletest
     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
 )

 include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
 link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -fprofile-arcs -ftest-coverage")
 enable_testing()

 file(GLOB TESTS "${CMAKE_SOURCE_DIR}/test/main.cpp")
 add_executable(runUnitTests  ${TESTS} ${SRC_LIST})
 target_link_libraries(runUnitTests gtest gtest_main pthread)
 add_test(NAME first-test COMMAND runUnitTests)


endif()
