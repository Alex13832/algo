# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
PROJECT(Algorithm)

set(HEADER_FILES string_algorithms.hpp)
set(SOURCE_FILES string_algorithms.cpp)

add_library(string STATIC ${SOURCE_FILES} ${HEADER_FILES})