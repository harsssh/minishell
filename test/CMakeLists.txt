cmake_minimum_required(VERSION 3.22)
project(minishell_test)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_libraries(ft GTest::gtest GTest::gtest_main)

file(GLOB VAR_SRC ${CMAKE_SOURCE_DIR}/src/variable/*.c)
add_executable(test_variable variable.cpp ${VAR_SRC})
target_include_directories(test_variable PUBLIC ${CMAKE_SOURCE_DIR}/src/variable)

add_executable(test_builtin_echo builtin_echo.cpp ${CMAKE_SOURCE_DIR}/src/builtin/echo.c)

gtest_discover_tests(test_builtin_echo test_variable)
