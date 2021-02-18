# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_executable(minimum_enclosing_circle_example mec_example.cpp)
target_link_libraries(minimum_enclosing_circle_example ${CMAKE_PROJECT_NAME})