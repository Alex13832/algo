# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(algo)

find_package(OpenCV REQUIRED)

add_executable(image_detect_hough_lines_run detect_hough_lines_example.cpp)
target_link_libraries(image_detect_hough_lines_run ${OpenCV_LIBS})
target_link_libraries(image_detect_hough_lines_run algo)
target_link_libraries(image_detect_hough_lines_run image_helpers)

add_executable(image_detect_corners_run detect_corners_example.cpp)
target_link_libraries(image_detect_corners_run ${OpenCV_LIBS})
target_link_libraries(image_detect_corners_run algo)
target_link_libraries(image_detect_corners_run image_helpers)

add_executable(image_canny_run detect_canny_edges_example.cpp)
target_link_libraries(image_canny_run ${OpenCV_LIBS})
target_link_libraries(image_canny_run algo)
target_link_libraries(image_canny_run image_helpers)