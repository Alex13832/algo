# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

if (OPENCV_INSTALLED=1)
    find_package(OpenCV REQUIRED)

    add_library(image_helpers STATIC image_helpers.cpp)
    target_link_libraries(image_helpers ${OpenCV_LIBS})
    target_link_libraries(image_helpers ${CMAKE_PROJECT_NAME})

    add_subdirectory(feature)
    add_subdirectory(filters)
    add_subdirectory(object)

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testfiles
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

endif()
