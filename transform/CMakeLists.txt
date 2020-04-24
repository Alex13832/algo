
PROJECT(Algorithm)

set(HEADER_FILES
        transform_algorithms.hpp
        )

set(SOURCE_FILES
        transform_algorithms.cpp
        )

add_library(transform STATIC ${SOURCE_FILES} ${HEADER_FILES})