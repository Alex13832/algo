project(AlgorithmTests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Algorithm_test_run
        test_string_bitap.cpp
        test_string_boyer_more.cpp
        test_string_longest_common_substr.cpp
        test_string_rabin_karp.cpp
        )

target_link_libraries(Algorithm_test_run string)
target_link_libraries(Algorithm_test_run gtest gtest_main)