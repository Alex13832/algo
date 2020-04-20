cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_COMPILER "gcc")

project(Algorithm)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(Algorithm_run ${SOURCE_FILES})

include_directories(string)
add_subdirectory(string)

include_directories(sort)
add_subdirectory(sort)

include_directories(maths)
add_subdirectory(maths)

include_directories(search)
add_subdirectory(search)

target_link_libraries(Algorithm_run string sort maths search)

add_subdirectory(test)