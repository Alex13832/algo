# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_COMPILER "gcc")
PROJECT(Algorithm LANGUAGES "CXX" VERSION "2.0.1")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")

# ////////////////////////////////////////
# Includes
# ////////////////////////////////////////

include_directories(data_mining)
add_subdirectory(data_mining)

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

# ////////////////////////////////////////
# Link
# ////////////////////////////////////////

add_library(algo INTERFACE)
target_link_libraries(algo INTERFACE data_mining geometry greedy maths network search sequence sort string transform)


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

# K-means example
target_link_libraries(kmeans_run algo)