# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(algo)

find_package(OpenCV REQUIRED)

include_directories(${ImageMagick_INCLUDE_DIRS})

add_executable(image_filter_run image_filter_example.cpp)
target_link_libraries(image_filter_run ${OpenCV_LIBS})
target_link_libraries(image_filter_run algo)