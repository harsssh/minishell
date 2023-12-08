#!/bin/bash

cd "$(dirname "$0")"

# テストケースをtestsディレクトリから取得して、拡張子を除いたファイル名のリストを作成
tests=$(find tests -type f -name '*.in' -or -name '*.err' | sort)
is_failed=0

for test in $tests
do
    # testsを先頭から削除して、拡張子を除いた文字列をtest_nameに代入
    test_name=$(echo $test | sed 's/^tests\///' | sed 's/\.[^.]*$//')
    # 拡張子を取得して、.errか判定してis_err_caseに代入
    is_err_case=$(echo $test | grep -q '\.err$' && echo 1 || echo 0)
    test_dir=$(dirname $test_name)

    mkdir -p diff/$test_dir

    ../minishell < $test &> diff/$test_name.out
    exit_status=$?
    diff -u --color tests/$test_name.expected diff/$test_name.out > /dev/null
    is_diff=$?

    if [[ $is_diff -ne 0 || ($is_err_case -eq 1 && $exit_status -eq 0) ]]
    then
        is_failed=1
        printf "$test \033[31mfailed\033[m\n" >&2
        if [ $is_err_case -eq 1 -a $exit_status -eq 0 ]
        then
            printf "  └── exit status: expected non-zero, but got 0\n" >&2;
        fi
        if [ $is_diff -ne 0 ]
        then
            diff -u --color tests/$test_name.expected diff/$test_name.out
        fi
    else
        printf "$test \033[32mpassed\033[m\n"
    fi
done

exit $is_failed
