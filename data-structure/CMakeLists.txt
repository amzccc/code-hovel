cmake_minimum_required(VERSION 3.20.0)

project(data_structures)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_LIST main.cpp)

set(target "test")

add_executable(${target} ${SOURCE_LIST})

add_subdirectory(tree)

add_subdirectory(hash-table)

add_subdirectory(graph)