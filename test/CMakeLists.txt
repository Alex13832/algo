project(AlgorithmTests)

add_subdirectory(lib)

add_executable(Algorithm_test_run
        test_greedy_algorithms.cpp
        test_math_algorithms.cpp
        test_search_algorithms.cpp
        test_sequence_algorithms.cpp
        test_sort_algorithms.cpp
        test_string_algorithms.cpp
        test_transform_algorithms.cpp
        )


target_link_libraries(Algorithm_test_run string sort search maths sequence greedy transform gtest gtest_main)
