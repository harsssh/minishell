cmake_minimum_required(VERSION 3.22)
project(minishell_test)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_libraries(ft GTest::gtest GTest::gtest_main)

file(GLOB VAR_SRC ${CMAKE_SOURCE_DIR}/src/variable/*.c)
file(GLOB BUILTIN_SRC ${CMAKE_SOURCE_DIR}/src/builtin/*.c)

# variable
add_executable(test_variable variable.cpp ${VAR_SRC})
target_include_directories(test_variable PUBLIC ${CMAKE_SOURCE_DIR}/src/variable)

# builtin
add_executable(test_builtin_echo builtin_echo.cpp ${BUILTIN_SRC})
add_executable(test_builtin_env builtin_env.cpp ${BUILTIN_SRC} ${VAR_SRC})

gtest_discover_tests(test_builtin_echo test_builtin_env test_variable)
