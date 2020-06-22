# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_executable(algo_graph_nn_run nn_example.cpp)
target_link_libraries(algo_graph_nn_run ${CMAKE_PROJECT_NAME})