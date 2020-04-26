PROJECT(Algorithm)

set(HEADER_FILES
        math_algorithms.hpp
        )

set(SOURCE_FILES
        math_algorithms.cpp
        )

add_library(maths STATIC ${SOURCE_FILES} ${HEADER_FILES})