cmake_minimum_required(VERSION 3.22)
project(minishell_test)

set(CMAKE_CXX_STANDARD 17)

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
link_libraries(ft GTest::gtest GTest::gtest_main ${CMAKE_BINARY_DIR}/readline/lib/libreadline.a ncurses)

# SRCをオブジェクトライブラリにする
add_library(src_obj OBJECT ${SRC})

add_executable(test_variables variables.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_variables)

add_executable(test_parse_variable_assignment parse_variable_assignment.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_parse_variable_assignment)

add_executable(test_get_next_option get_next_option.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_get_next_option)

add_executable(test_builtins_echo builtins_echo.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_builtins_echo)

add_executable(test_builtins_env builtins_env.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_builtins_env)

add_executable(test_builtins_unset builtins_unset.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_builtins_unset)

add_executable(test_builtins_exit builtins_exit.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_builtins_exit)

add_executable(test_builtins_export builtins_export.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_builtins_export)

add_executable(test_join_path join_path.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_join_path)

add_executable(test_canonicalize_absolute_path canonicalize_absolute_path.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_canonicalize_absolute_path)

add_executable(test_lexer lexer.cpp utils/compare_list.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_lexer)

add_executable(test_parser parser.cpp utils/ast_builder.cpp utils/compare_ast.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_parser)

add_executable(test_word_expansion word_expansion.cpp utils/context.cpp $<TARGET_OBJECTS:src_obj>)
gtest_discover_tests(test_word_expansion)

