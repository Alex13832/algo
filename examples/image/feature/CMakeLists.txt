# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(algo)

find_package(OpenCV REQUIRED)

add_executable(image_detect_corners_run algo_image_feature_corners_example.cpp)
target_link_libraries(image_detect_corners_run ${OpenCV_LIBS})
target_link_libraries(image_detect_corners_run algo)
target_link_libraries(image_detect_corners_run image_helpers)

add_executable(image_hough_transform_example_run algo_image_feature_hough_transform_example.cpp)
target_link_libraries(image_hough_transform_example_run ${OpenCV_LIBS})
target_link_libraries(image_hough_transform_example_run algo)
target_link_libraries(image_hough_transform_example_run image_helpers)
