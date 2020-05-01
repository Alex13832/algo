# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
PROJECT(Algorithm)

set(HEADER_FILES data_mining_algorithms.hpp)

set(SOURCE_FILES data_mining_algorithms.cpp)

add_library(data_mining STATIC ${SOURCE_FILES} ${HEADER_FILES})