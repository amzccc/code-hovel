cmake_minimum_required(VERSION 3.20.0)

project(export-demo CXX)

add_library(calc STATIC calc.cpp)

set(EXPORT_DIR "${CMAKE_CURRENT_BINARY_DIR}/cmake")

export(TARGETS calc FILE "${EXPORT_DIR}/CalcTargets.cmake" NAMESPACE calc::)

