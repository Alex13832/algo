project(AlgorithmTests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Algorithm_test_run
        test_string.cpp
        )

target_link_libraries(Algorithm_test_run string)
target_link_libraries(Algorithm_test_run gtest gtest_main)