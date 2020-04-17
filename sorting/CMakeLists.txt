PROJECT(Algorithm)

set(HEADER_FILES
        sort_algorithms.hpp
        )

set(SOURCE_FILES
        sort_algorithms.cpp
        )

add_library(sorting STATIC ${SOURCE_FILES} ${HEADER_FILES})