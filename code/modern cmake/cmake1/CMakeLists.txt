cmake_minimum_required(VERSION 3.20)

project(hello-CMake LANGUAGES CXX)

add_executable(hello main.cpp)

add_library(mylib STATIC some.hpp some.cpp)

target_link_libraries(hello mylib)

add_library(objs OBJECT some.hpp some.cpp)

add_library(mylib-static STATIC $<TARGET_OBJECTS:objs>)

set_target_properties(mylib-static PROPERTIES OUTPUT_NAME "mylib")

add_library(mylib-shared SHARED $<TARGET_OBJECTS:objs>)

set_target_properties(mylib-shared PROPERTIES OUTPUT_NAME "mylib")

set(use_lib OFF)

if(use_lib)
    add_library(mylib STATIC some.hpp some.cpp)
else()
    add_library(mylib SHARED some.hpp some.cpp)
endif()

list(APPEND src else.hpp else.cpp)

option(use_lib_flag "switch" OFF)
if(use_lib_flag)
    add_library(mylib STATIC some.hpp some.cpp)
endif()