PROJECT(Algorithm)

set(HEADER_FILES
        sequence_algorithms.hpp
        )

set(SOURCE_FILES
        sequence_algorithms.cpp
        )

add_library(sequence STATIC ${SOURCE_FILES} ${HEADER_FILES})