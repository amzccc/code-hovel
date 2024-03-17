cmake_minimum_required(VERSION 3.20.0)

project(data_structures)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_LIST main.cpp)

add_subdirectory(tree)

add_executable(test ${SOURCE_LIST})