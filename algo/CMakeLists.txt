# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.12)
project(${CMAKE_PROJECT_NAME} CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(ALGO_SRCS
        ${PROJECT_SOURCE_DIR}/algo_data_mining.cpp
        ${PROJECT_SOURCE_DIR}/algo_geometry.cpp
        ${PROJECT_SOURCE_DIR}/algo_geometry_ds.cpp
        ${PROJECT_SOURCE_DIR}/algo_graph.cpp
        ${PROJECT_SOURCE_DIR}/algo_greedy.cpp
        ${PROJECT_SOURCE_DIR}/algo_image_basic.cpp
        ${PROJECT_SOURCE_DIR}/algo_image_feature.cpp
        ${PROJECT_SOURCE_DIR}/algo_image_filter.cpp
        ${PROJECT_SOURCE_DIR}/algo_image_object.cpp
        ${PROJECT_SOURCE_DIR}/algo_math.cpp
        ${PROJECT_SOURCE_DIR}/algo_network.cpp
        ${PROJECT_SOURCE_DIR}/algo_puzzle.cpp
        ${PROJECT_SOURCE_DIR}/algo_search.cpp
        ${PROJECT_SOURCE_DIR}/algo_sequence.cpp
        ${PROJECT_SOURCE_DIR}/algo_sort.cpp
        ${PROJECT_SOURCE_DIR}/algo_string.cpp
        ${PROJECT_SOURCE_DIR}/algo_transform.cpp
        )

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${CMAKE_PROJECT_NAME} SHARED ${ALGO_SRCS})
