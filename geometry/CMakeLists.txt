# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
PROJECT(Algorithm)

set(GEOMETRY_HEADER_FILES geometry_algorithms.hpp)

set(GEOMETRY_SOURCE_FILES geometry_algorithms.cpp)

add_library(geometry STATIC ${GEOMETRY_HEADER_FILES} ${GEOMETRY_SOURCE_FILES})