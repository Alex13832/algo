PROJECT(Algorithm)

set(HEADER_FILES
        search_algorithms.hpp
        )

set(SOURCE_FILES
        search_algorithms.cpp
        )

add_library(search STATIC ${SOURCE_FILES} ${HEADER_FILES})