enable_testing()

add_executable(unit-test unit_test.cpp ${CMAKE_SOURCE_DIR}/src/calc.cpp)

target_include_directories(unit-test PRIVATE "${CMAKE_SOURCE_DIR}/src")

add_test(NAME sumTwoInts COMMAND unit-test 1)

add_test(NAME multiplyTwoInts COMMAND unit-test 2)