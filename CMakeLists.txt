cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_COMPILER "gcc")

project(Algorithm)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(Algorithm_run ${SOURCE_FILES})

include_directories(greedy)
add_subdirectory(greedy)

include_directories(maths)
add_subdirectory(maths)

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

target_link_libraries(Algorithm_run greedy maths search sequence sort string transform)

include_directories(test/testfiles)
add_subdirectory(test)