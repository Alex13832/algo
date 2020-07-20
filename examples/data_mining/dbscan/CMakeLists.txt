# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_executable(algo_data_mining_dbscan_run dbscan_example.cpp)
target_link_libraries(algo_data_mining_dbscan_run ${CMAKE_PROJECT_NAME})