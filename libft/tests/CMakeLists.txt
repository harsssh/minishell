cmake_minimum_required(VERSION 3.14)
project(libft_test)

set(CMAKE_CXX_STANDARD 14)

# Google Test v1.14.0
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        f8d7d77c06936315286eb55f8de22cd23c188571
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_libraries(ft gtest gtest_main)

add_executable(test_list list.cpp)
gtest_discover_tests(test_list)

add_executable(test_basename basename.cpp)
gtest_discover_tests(test_basename)
