project(AlgorithmTests)

add_subdirectory(lib)

file(GLOB test_SRC "*.cpp")

add_executable(Algorithm_test_run ${test_SRC})

target_link_libraries(Algorithm_test_run algo gtest gtest_main)
