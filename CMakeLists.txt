# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_COMPILER "gcc")
PROJECT(Algorithm CXX)
set(CMAKE_CXX_STANDARD 17)

# ////////////////////////////////////////
# Includes
# ////////////////////////////////////////

include_directories(geometry)
add_subdirectory(geometry)

include_directories(greedy)
add_subdirectory(greedy)

include_directories(math)
add_subdirectory(math)

include_directories(network)
add_subdirectory(network)

include_directories(search)
add_subdirectory(search)

include_directories(sequence)
add_subdirectory(sequence)

include_directories(sort)
add_subdirectory(sort)

include_directories(string)
add_subdirectory(string)

include_directories(transform)
add_subdirectory(transform)

add_library(algo INTERFACE)
target_link_libraries(algo INTERFACE geometry greedy maths network search sequence sort string transform)

# ////////////////////////////////////////
# Test
# ////////////////////////////////////////

add_subdirectory(test)

# ////////////////////////////////////////
# Examples
# ////////////////////////////////////////

include_directories(examples)
add_subdirectory(examples)

# Quickhull example:
target_link_libraries(qhull_run algo)