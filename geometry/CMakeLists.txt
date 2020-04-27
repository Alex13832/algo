PROJECT(Algorithm)

set(HEADER_FILES
        geometry_algorithms.hpp
        )

set(SOURCE_FILES
        geometry_algorithms.cpp
        )

add_library(geometry STATIC ${SOURCE_FILES} ${HEADER_FILES})