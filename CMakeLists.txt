# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.12)
PROJECT(algo LANGUAGES "CXX")
set(CMAKE_CXX_STANDARD 17)

# Enable coverage
option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
# Enable coverage locally
option(ENABLE_COVERAGE_LOCALLY "Enable coverage locally for gcc/clang" FALSE)
# Enable tests
option(COMPILE_EXAMPLES "Compile the source code for the examples" FALSE)
# Tell cmake that OpenCV is installed
option(OPENCV_INSTALLED "This computer has OpenCV installed" FALSE)

if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
endif ()

if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wno-missing-braces -Wmissing-field-initializers)
endif ()

enable_testing()

if (ENABLE_COVERAGE_LOCALLY)
    set(CMAKE_C_COMPILER "gcc")
#    set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage ")
endif ()

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
# Examples
# ////////////////////////////////////////
if (COMPILE_EXAMPLES)
    include_directories(examples)
    add_subdirectory(examples)
endif ()
