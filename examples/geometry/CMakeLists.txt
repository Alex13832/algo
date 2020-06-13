# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(Algorithm)

add_subdirectory(closest_pair)
include_directories(closest_pair)

add_subdirectory(convex_hull)
include_directories(convex_hull)

add_subdirectory(triangulate)
include_directories(triangulate)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testfiles
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})