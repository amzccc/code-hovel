cmake_minimum_required(VERSION 3.22)

project(InterfaceAndImpl)

add_executable(main main.cpp drived_impl.cpp drived.cpp base_impl.cpp base.cpp)

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR})

