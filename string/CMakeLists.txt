PROJECT(Algorithm)

set(HEADER_FILES
        string_algorithms.h
        )

set(SOURCE_FILES
        bitap.cpp
        boyer_moore.cpp
        longest_common_substr.cpp
        rabin_karp.cpp
        )

add_library(string STATIC ${SOURCE_FILES} ${HEADER_FILES})