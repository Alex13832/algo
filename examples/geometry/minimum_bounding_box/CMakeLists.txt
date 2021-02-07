# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_executable(minimum_bounding_box_example mbbox_example.cpp)
target_link_libraries(minimum_bounding_box_example ${CMAKE_PROJECT_NAME})