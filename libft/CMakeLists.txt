cmake_minimum_required(VERSION 3.22)
project(libft C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

file(GLOB SOURCES *.c **/*.c)

add_library(ft STATIC ${SOURCES})
target_include_directories(ft PUBLIC include)