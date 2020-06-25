# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 2.8.8)
if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)
PROJECT(algo LANGUAGES "CXX")


set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage ")

# ////////////////////////////////////////
# Includes
# ////////////////////////////////////////
include_directories(algo)
add_subdirectory(algo)

# ////////////////////////////////////////
# Test, needs Google Test
# ////////////////////////////////////////
add_subdirectory(test)

# ////////////////////////////////////////
# Examples, needs OpenCv,
# uncomment to build
# ////////////////////////////////////////
#include_directories(examples)
#add_subdirectory(examples)
