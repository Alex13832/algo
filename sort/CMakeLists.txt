# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
PROJECT(Algorithm)

set(HEADER_FILES sort_algorithms.hpp)
set(SOURCE_FILES sort_algorithms.cpp)

add_library(sort STATIC ${SOURCE_FILES} ${HEADER_FILES})