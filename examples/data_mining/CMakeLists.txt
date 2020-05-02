# //////////////////////////////////////////////////////////
# author: alex011235
# https://github.com/alex011235/algorithm
# //////////////////////////////////////////////////////////
project(algo)

add_executable(kmeans_run kmeans_example.cpp)
target_link_libraries(kmeans_run algo)

add_executable(knn_run knn_example.cpp)
target_link_libraries(knn_run algo)
