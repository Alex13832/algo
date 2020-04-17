PROJECT(Algorithm)

set(HEADER_FILES
        string_algorithms.hpp
        )

set(SOURCE_FILES
        string_algorithms.cpp
        )

add_library(string STATIC ${SOURCE_FILES} ${HEADER_FILES})