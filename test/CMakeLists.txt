cmake_minimum_required(VERSION 3.22)
project(minishell_test)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

# src/main.c 以外のファイル
file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/src/*/*.c)
# src直下のディレクトリ
file(GLOB TMP ${CMAKE_SOURCE_DIR}/src/*)
set(DIR_LIST "")
foreach (TMP_PATH ${TMP})
    if (IS_DIRECTORY ${TMP_PATH})
        list(APPEND DIR_LIST ${TMP_PATH})
    endif ()
endforeach ()

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src ${DIR_LIST})
link_libraries(ft GTest::gtest GTest::gtest_main)

add_executable(test_variable variable.cpp ${SRC})
gtest_discover_tests(test_variable)

add_executable(test_variable_parse variable_parse.cpp ${SRC})
gtest_discover_tests(test_variable_parse)

add_executable(test_get_next_option get_next_option.cpp ${SRC})
gtest_discover_tests(test_get_next_option)

add_executable(test_builtin_echo builtin_echo.cpp ${SRC})
gtest_discover_tests(test_builtin_echo)

add_executable(test_builtin_env builtin_env.cpp ${SRC})
gtest_discover_tests(test_builtin_env)

add_executable(test_builtin_unset builtin_unset.cpp ${SRC})
gtest_discover_tests(test_builtin_unset)

add_executable(test_builtin_exit builtin_exit.cpp ${SRC})
gtest_discover_tests(test_builtin_exit)

add_executable(test_builtin_export builtin_export.cpp ${SRC})
gtest_discover_tests(test_builtin_export)

add_executable(test_join_path join_path.cpp ${SRC})
gtest_discover_tests(test_join_path)

add_executable(test_canonicalize_path canonicalize_path.cpp ${SRC})
gtest_discover_tests(test_canonicalize_path)