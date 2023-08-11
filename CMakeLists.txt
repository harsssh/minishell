cmake_minimum_required(VERSION 3.22)
project(minishell C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_subdirectory(libft)
add_subdirectory(test)

file(GLOB_RECURSE SRC src/*.c)

add_executable(minishell ${SRC})
target_link_libraries(minishell ft)
target_include_directories(minishell PRIVATE include)
