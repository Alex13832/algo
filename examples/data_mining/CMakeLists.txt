# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

set(libs
        ${CMAKE_PROJECT_NAME}
        common)

add_executable(algo_data_mining_examples_run data_mining_examples.cpp)
target_link_libraries(algo_data_mining_examples_run ${libs})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testfiles
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})