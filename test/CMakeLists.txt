cmake_minimum_required(VERSION 3.22)
project(test)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
find_package(GTest CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_libraries(ft GTest::gtest GTest::gtest_main)