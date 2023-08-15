cmake_minimum_required(VERSION 3.22)
project(minishell_test)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_libraries(ft GTest::gtest GTest::gtest_main)

file(GLOB VAR_SRC ${CMAKE_SOURCE_DIR}/src/variable/*.c)
add_executable(test_varibale variable.cpp ${VAR_SRC})
target_include_directories(test_varibale PUBLIC ${CMAKE_SOURCE_DIR}/src/variable)

gtest_discover_tests(test_varibale)