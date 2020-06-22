# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_executable(algo_geometry_triangulate_run triangulate_example.cpp)
target_link_libraries(algo_geometry_triangulate_run ${CMAKE_PROJECT_NAME})