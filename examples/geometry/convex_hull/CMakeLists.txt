# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_executable(algo_geometry_convex_hull_run qhull_example.cpp)
target_link_libraries(algo_geometry_convex_hull_run ${CMAKE_PROJECT_NAME})