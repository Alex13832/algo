# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(algo)

find_package(OpenCV REQUIRED)

add_library(image_helpers STATIC image_helpers.cpp)
target_link_libraries(image_helpers ${OpenCV_LIBS})
target_link_libraries(image_helpers algo)

add_subdirectory(detection)

add_subdirectory(filters)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testfiles
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})