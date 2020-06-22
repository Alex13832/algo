# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

find_package(OpenCV REQUIRED)

add_executable(algo_image_detect_hough_lines_run algo_image_object_lines_example.cpp)
target_link_libraries(algo_image_detect_hough_lines_run ${OpenCV_LIBS})
target_link_libraries(algo_image_detect_hough_lines_run ${CMAKE_PROJECT_NAME})
target_link_libraries(algo_image_detect_hough_lines_run image_helpers)

add_executable(algo_image_canny_run algo_image_object_canny_edge_example.cpp)
target_link_libraries(algo_image_canny_run ${OpenCV_LIBS})
target_link_libraries(algo_image_canny_run ${CMAKE_PROJECT_NAME})
target_link_libraries(algo_image_canny_run image_helpers)