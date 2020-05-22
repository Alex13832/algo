# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(algo)

find_package(OpenCV REQUIRED)

add_executable(image_filter_run image_filter_example.cpp)
target_link_libraries(image_filter_run ${OpenCV_LIBS})
target_link_libraries(image_filter_run algo)
target_link_libraries(image_filter_run image_helpers)

add_executable(image_transform_run image_transform_example.cpp)
target_link_libraries(image_transform_run ${OpenCV_LIBS})
target_link_libraries(image_transform_run algo)
target_link_libraries(image_transform_run image_helpers)