# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_executable(algo_sort_run algo_sort_example.cpp)
target_link_libraries(algo_sort_run ${CMAKE_PROJECT_NAME})