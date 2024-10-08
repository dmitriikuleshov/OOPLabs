cmake_minimum_required(VERSION 3.10)
project(LabWork1)

# Set C++ standarts
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Include compilation options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

find_package(GTest QUIET)
if(NOT GTest_FOUND)
  # Install Google Test
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    TLS_VERIFY false
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include)

add_library(lab2_lib include/array.hpp main.cpp include/twelve_digit.hpp src/twelve_digit.cpp include/twelve.hpp src/twelve.cpp)

add_executable(main_file_exe main.cpp)
target_link_libraries(main_file_exe PRIVATE lab2_lib)

# Tests
enable_testing()
# Array tests
add_executable(array_tests tests/array_tests.cpp)
find_package(GTest REQUIRED)
target_link_libraries(array_tests GTest::GTest GTest::Main lab2_lib)
add_test(NAME array_tests COMMAND array_tests)

add_executable(twelve_tests tests/twelve_tests.cpp)
target_link_libraries(twelve_tests GTest::GTest GTest::Main lab2_lib)
add_test(NAME twelve_tests COMMAND twelve_tests)

# TwelveDigit tests
add_executable(twelve_digit_tests tests/twelve_digit_tests.cpp)
target_link_libraries(twelve_digit_tests GTest::GTest GTest::Main lab2_lib)
add_test(NAME twelve_digit_tests COMMAND twelve_digit_tests)

