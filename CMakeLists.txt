cmake_minimum_required(VERSION 2.7)

project(thread_manager)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAG} "-std=c99")
option(test "Build all tests." OFF)

file(GLOB SRC "src/*.c")
file(GLOB HEADER "src/*.h")



if (test)
 include(ExternalProject)

 set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

 ExternalProject_Add(googletest
     GIT_REPOSITORY https://github.com/google/googletest
     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
 )

 include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
 link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
 enable_testing()

 file(GLOB TESTS "/tests/*.cpp")
 add_executable(runUnitTests  ${TESTS} ${SRC}  ${HEADER})
 target_link_libraries(runUnitTests gtest gtest_main pthread)
 add_test(NAME first-test COMMAND runUnitTests)


endif()


add_executable(thread_manager ${SRC} ${HEADER})
