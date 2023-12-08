#!/bin/bash

# 引数をチェック
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 category/name.[in|err]"
    exit 1
fi

# 引数からカテゴリと名前を取得（拡張子は除外）
input_path=$1
category=$(dirname "$input_path")
base_name=$(basename "$input_path")
name=${base_name%.*}

# tests/ディレクトリが存在しなければ作成
if [ ! -d tests ]; then
    mkdir tests
fi

# カテゴリディレクトリが存在しなければ作成
if [ ! -d "tests/$category" ]; then
    mkdir -p "tests/$category"
fi

# 入力ファイル（.in または .err）と .expected ファイルを作成
touch "tests/$input_path"
touch "tests/$category/$name.expected"

echo "$input_path and $category/$name.expected created in tests/ directory."
