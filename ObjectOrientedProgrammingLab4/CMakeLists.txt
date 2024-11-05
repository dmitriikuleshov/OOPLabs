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

# Пути к include и src директориям
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

# Подключаем GTest
find_package(GTest REQUIRED)
include_directories(${INCLUDE_DIR})

# Компилируем главный исполняемый файл
add_executable(main_file_exe main.cpp)

# Настройка тестов
enable_testing()

# Функция для добавления тестов
function(add_gtest_executable TEST_NAME TEST_SRC)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} GTest::GTest GTest::Main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

# Добавляем тесты
add_gtest_executable(array_tests ${TEST_DIR}/array_tests.cpp)
add_gtest_executable(polygonal_tests ${TEST_DIR}/polygonal_tests.cpp)