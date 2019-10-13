PROJECT(Algorithm)

set(HEADER_FILES
        string_algorithms.h
        )

set(SOURCE_FILES
        bitap.cpp
        boyer_moore.cpp
        )

add_library(string STATIC ${SOURCE_FILES} ${HEADER_FILES})