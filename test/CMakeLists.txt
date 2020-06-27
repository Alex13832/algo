# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
cmake_minimum_required(VERSION 3.12)
project(AlgorithmTests)

# Include Google Test
add_subdirectory(gtest)
include_directories(gtest)
file(GLOB test_SRC "*.cpp")

add_executable(algo_tests ${test_SRC})

target_link_libraries(algo_tests ${CMAKE_PROJECT_NAME})
target_link_libraries(algo_tests gtest gtest_main)
target_link_libraries(algo_tests --coverage)
add_test(AlgoTests algo_tests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testfiles
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

