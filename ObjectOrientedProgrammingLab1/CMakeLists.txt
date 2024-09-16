cmake_minimum_required(VERSION 3.10)
project(LabWork)

# Set C++ standarts
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Initial files
add_library(to_binary_string src/to_binary_string.cpp)
# Tests
enable_testing()
add_executable(unit_tests tests/unit_tests.cpp)
find_package(GTest REQUIRED)
target_link_libraries(unit_tests GTest::GTest GTest::Main)
add_test(NAME unit_tests COMMAND unit_tests)
