# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(algo)

find_package(OpenCV REQUIRED)

add_library(image_helpers STATIC image_helpers.cpp)
target_link_libraries(image_helpers ${OpenCV_LIBS})
target_link_libraries(image_helpers algo)

include_directories(filters)
add_subdirectory(filters)
