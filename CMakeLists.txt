# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_COMPILER "gcc")
PROJECT(algo LANGUAGES "CXX" VERSION "2.0.1")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")

# ////////////////////////////////////////
# Includes
# ////////////////////////////////////////

include_directories(algo)
add_subdirectory(algo)

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
# Closest pair example:
target_link_libraries(closest_pair_run algo)
# Triangulate example:
target_link_libraries(triangulate_run algo)
