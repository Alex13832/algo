# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
PROJECT(Algorithm)

set(HEADER_FILES sequence_algorithms.hpp)
set(SOURCE_FILES sequence_algorithms.cpp)

add_library(sequence STATIC ${SOURCE_FILES} ${HEADER_FILES})