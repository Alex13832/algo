PROJECT(Algorithm)

set(HEADER_FILES
        sorting_algorithms.h
        )

set(SOURCE_FILES
        bubble_sort.cpp
        merge_sort.cpp
        )

add_library(sorting STATIC ${SOURCE_FILES} ${HEADER_FILES})