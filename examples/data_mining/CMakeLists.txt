# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

add_subdirectory(kmeans)
add_subdirectory(knn)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testfiles
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})