# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

set(LIBS
        ${CMAKE_PROJECT_NAME}
        common)

add_executable(algo_graph_examples_run graph_examples.cpp)
target_link_libraries(algo_graph_examples_run ${LIBS})
