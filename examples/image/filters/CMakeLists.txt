# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

find_package(OpenCV REQUIRED)

add_executable(algo_image_filter_run algo_image_filter_example.cpp)
target_link_libraries(algo_image_filter_run ${OpenCV_LIBS})
target_link_libraries(algo_image_filter_run ${CMAKE_PROJECT_NAME})
target_link_libraries(algo_image_filter_run image_helpers)
