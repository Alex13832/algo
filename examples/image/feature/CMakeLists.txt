# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

find_package(OpenCV REQUIRED)

add_executable(algo_image_detect_corners_run algo_image_feature_corners_example.cpp)
target_link_libraries(algo_image_detect_corners_run ${OpenCV_LIBS})
target_link_libraries(algo_image_detect_corners_run ${CMAKE_PROJECT_NAME})
target_link_libraries(algo_image_detect_corners_run image_helpers)

add_executable(algo_image_hough_transform_example_run algo_image_feature_hough_transform_example.cpp)
target_link_libraries(algo_image_hough_transform_example_run ${OpenCV_LIBS})
target_link_libraries(algo_image_hough_transform_example_run ${CMAKE_PROJECT_NAME})
target_link_libraries(algo_image_hough_transform_example_run image_helpers)
