cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_COMPILER "gcc")

project(Algorithm)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(Algorithm_run ${SOURCE_FILES})

include_directories(string)
add_subdirectory(string)

include_directories(sorting)
add_subdirectory(sorting)

target_link_libraries(Algorithm_run string sorting)

add_subdirectory(test)