# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
PROJECT(Algorithm)

set(HEADER_FILES network_algorithms.hpp)
set(SOURCE_FILES network_algorithms.cpp)

add_library(network STATIC ${SOURCE_FILES} ${HEADER_FILES})