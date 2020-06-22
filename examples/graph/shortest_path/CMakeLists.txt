# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_executable(algo_graph_shortest_path_run shortest_path_example.cpp)
target_link_libraries(algo_graph_shortest_path_run ${CMAKE_PROJECT_NAME})