# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(${CMAKE_PROJECT_NAME})

include_directories(common)
add_subdirectory(common)

include_directories(data_mining)
add_subdirectory(data_mining)

include_directories(geometry)
add_subdirectory(geometry)

include_directories(graph)
add_subdirectory(graph)

if (OPENCV_INSTALLED)
    include_directories(image)
    add_subdirectory(image)
endif ()

include_directories(sort)
add_subdirectory(sort)