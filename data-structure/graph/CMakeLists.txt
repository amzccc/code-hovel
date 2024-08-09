cmake_minimum_required(VERSION 3.20)

list(APPEND SOURCE_LIST *.hpp *.cpp)

target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})