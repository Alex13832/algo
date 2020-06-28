# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.12)
PROJECT(algo LANGUAGES "CXX")
set(CMAKE_CXX_STANDARD 17)

# Enable coverage

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
endif ()


if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif ()

enable_testing()

#set(CMAKE_C_COMPILER "gcc")
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
