# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
PROJECT(Algorithm)

set(HEADER_FILES math_algorithms.hpp)
set(SOURCE_FILES math_algorithms.cpp)

add_library(maths STATIC ${SOURCE_FILES} ${HEADER_FILES})