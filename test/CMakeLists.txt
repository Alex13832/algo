# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
cmake_minimum_required(VERSION 3.14)
project(AlgorithmTests)

# Include Google Test
include(gtest.cmake)

file(GLOB test_SRC "*.cpp")

add_executable(algo_tests ${test_SRC})

target_link_libraries(algo_tests ${CMAKE_PROJECT_NAME})

# GTest needs threading support
find_package(Threads)
target_link_libraries(algo_tests gtest ${CMAKE_THREAD_LIBS_INIT})