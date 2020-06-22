# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_executable(algo_graph_mst_run mst_example.cpp)
target_link_libraries(algo_graph_mst_run ${CMAKE_PROJECT_NAME})