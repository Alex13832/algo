cmake_minimum_required(VERSION 3.14)
project(Algorithm)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(Algorithm_run ${SOURCE_FILES})

include_directories(string)
add_subdirectory(string)

target_link_libraries(Algorithm_run string)

add_subdirectory(test)