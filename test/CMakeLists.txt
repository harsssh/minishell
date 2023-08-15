cmake_minimum_required(VERSION 3.22)
project(test)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_libraries(ft GTest::gtest GTest::gtest_main)

add_executable(test_builtin_echo builtin_echo.cpp ${CMAKE_SOURCE_DIR}/src/builtin/echo.c)

gtest_discover_tests(test_builtin_echo)