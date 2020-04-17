PROJECT(Algorithm)

set(HEADER_FILES
        maths_algorithms.hpp
        )

set(SOURCE_FILES
        maths_algorithms.cpp
        )

add_library(maths STATIC ${SOURCE_FILES} ${HEADER_FILES})