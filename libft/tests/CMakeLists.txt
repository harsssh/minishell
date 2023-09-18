cmake_minimum_required(VERSION 3.22)
project(libft_test)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_libraries(ft GTest::gtest GTest::gtest_main)

add_executable(test_list list.cpp)
gtest_discover_tests(test_list)