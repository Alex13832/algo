# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
cmake_minimum_required(VERSION 3.14)
project(AlgorithmTests)

# Include Google Test
include(gtest.cmake)

file(GLOB test_SRC "*.cpp")

add_executable(Algorithm_test_run ${test_SRC})

target_link_libraries(Algorithm_test_run ${CMAKE_PROJECT_NAME})

# GTest needs threading support
find_package(Threads)
target_link_libraries(Algorithm_test_run gtest ${CMAKE_THREAD_LIBS_INIT})