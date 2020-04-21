PROJECT(Algorithm)

set(HEADER_FILES
        greedy_algorithms.hpp
        )

set(SOURCE_FILES
        greedy_algorithms.cpp
        )

add_library(greedy STATIC ${SOURCE_FILES} ${HEADER_FILES})