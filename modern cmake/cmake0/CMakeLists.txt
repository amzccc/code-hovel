cmake_minimum_required(VERSION 3.20)

project(configure LANGUAGES CXX)

add_executable(main src/main.cpp)

set(FOO_ENABLE ON)

set(FOO_STRING1 "abc")

set(FOO_STRING2 "def")

configure_file(src/configure.h.in configure.h)

target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR})

