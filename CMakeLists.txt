cmake_minimum_required(VERSION 3.22)
project(minishell C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

enable_testing()

add_subdirectory(libft)
add_subdirectory(tests)

# build readline
include(ExternalProject)
ExternalProject_Add(
        gnu_readline
        PREFIX ${CMAKE_BINARY_DIR}/readline
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/readline
        CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/readline/configure
        -q --prefix=${CMAKE_BINARY_DIR}/readline --enable-shared=no
        BUILD_COMMAND make
        BUILD_IN_SOURCE 1
        INSTALL_COMMAND make install
)

file(GLOB_RECURSE SRC src/*.c)
add_executable(minishell ${SRC})

add_dependencies(minishell gnu_readline)
target_include_directories(minishell PRIVATE src include ${CMAKE_BINARY_DIR}/readline/include)
target_link_libraries(minishell ft ${CMAKE_BINARY_DIR}/readline/lib/libreadline.a ncurses)
