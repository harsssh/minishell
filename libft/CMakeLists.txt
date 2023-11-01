cmake_minimum_required(VERSION 3.14)
project(libft C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")

enable_testing()

add_subdirectory(tests)

file(GLOB_RECURSE SOURCES *.c)
add_library(ft STATIC ${SOURCES})
target_include_directories(ft PUBLIC include)