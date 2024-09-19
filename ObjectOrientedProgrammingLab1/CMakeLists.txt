cmake_minimum_required(VERSION 3.10)
project(LabWork1)

# Set C++ standarts
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Include compilation options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

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


# Includes paths to header files of Google Test
# Shows the compiler where to look for Google Test headers
include_directories(${GTEST_INCLUDE_DIRS})

# Initial files
add_library(to_binary_string_lib src/to_binary_string.cpp)
target_include_directories(to_binary_string_lib PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(main_file_exe main.cpp)
target_link_libraries(main_file_exe PRIVATE to_binary_string_lib)
target_include_directories(main_file_exe PRIVATE ${CMAKE_SOURCE_DIR}/include)


# Tests
enable_testing()
# Create executable file (program with tests)
add_executable(unit_tests tests/unit_tests.cpp)
# Connect to_binary_string_lib to tests
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(GTest REQUIRED)
# Connect "unit_tests" to Google Test (GTest::GTest)
# Connect "unit_tests" to Google Test Main that includes main function (GTest::Main)
target_link_libraries(unit_tests GTest::GTest GTest::Main)
add_test(NAME unit_tests COMMAND unit_tests)
