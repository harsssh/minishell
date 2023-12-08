#!/bin/bash

cd "$(dirname "$0")"

# テストケースをtestsディレクトリから取得して、拡張子を除いたファイル名のリストを作成
tests=$(find tests -type f -name '*.in' | sort | sed -e 's/\..*$//')

for test in $tests
do
    # testsを先頭から削除した文字列をtest_nameに代入
    test_name=$(echo $test | sed -e 's/^tests\///')
    test_dir=$(dirname $test_name)
    mkdir -p diff/$test_dir
    printf "Running test \033[33m$test_name\033[m\n"
    ../minishell < $test.in > diff/$test_name.out
    diff -u --color $test.expected diff/$test_name.out >&2
    if [ $? -eq 0 ]
    then
        printf "Test $test \033[32mpassed\033[m\n"
    else
        printf "Test $test \033[31mfailed\033[m\n" >&2
    fi
done
