# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.14)
project(algo CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(ALGO_SRCS
        ${PROJECT_SOURCE_DIR}/data_mining_algorithms.cpp
        ${PROJECT_SOURCE_DIR}/geometry_algorithms.cpp
        ${PROJECT_SOURCE_DIR}/greedy_algorithms.cpp
        ${PROJECT_SOURCE_DIR}/math_algorithms.cpp
        ${PROJECT_SOURCE_DIR}/network_algorithms.cpp
        ${PROJECT_SOURCE_DIR}/search_algorithms.cpp
        ${PROJECT_SOURCE_DIR}/sequence_algorithms.cpp
        ${PROJECT_SOURCE_DIR}/sort_algorithms.cpp
        ${PROJECT_SOURCE_DIR}/string_algorithms.cpp
        ${PROJECT_SOURCE_DIR}/transform_algorithms.cpp
        )

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${PROJECT_NAME} SHARED ${ALGO_SRCS})
