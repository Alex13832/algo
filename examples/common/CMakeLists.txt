# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////

project(${CMAKE_PROJECT_NAME})

add_library(common STATIC io.cpp)
target_link_libraries(common ${CMAKE_PROJECT_NAME})