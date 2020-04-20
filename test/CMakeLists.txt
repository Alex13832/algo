project(AlgorithmTests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Algorithm_test_run
        test_math_algorithms.cpp
        test_search_algorithms.cpp
        test_sort_algorithms.cpp
        test_string_algorithms.cpp
        )

target_link_libraries(Algorithm_test_run string sort search maths gtest gtest_main)