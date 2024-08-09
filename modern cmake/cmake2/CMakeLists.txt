cmake_minimum_required(VERSION 3.20)

project(cmake2 LANGUAGES CXX)

file(GLOB Src *.cpp)

add_executable(target ${Src})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(target PUBLIC "IS_LINUX")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(target PUBLIC "IS_WINDOWS")
endif()



