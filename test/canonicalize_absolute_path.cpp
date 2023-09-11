#include <gtest/gtest.h>
extern "C" {
#include "cd/cd_internal.h"
}

// 正規化済みのパス
TEST(canonicalize_absolute_path, basic)
{
	char	*result;

	result = canonicalize_absolute_path("/path/to/dir", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// パスの最後が / で終わる
TEST(canonicalize_absolute_path, end_with_slash)
{
	char	*result;

	result = canonicalize_absolute_path("/path/to/dir/", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// ./ を含む
TEST(canonicalize_absolute_path, contain_dot)
{
	char	*result;

	result = canonicalize_absolute_path("/path/./to/dir", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// ../ を含む
TEST(canonicalize_absolute_path, contain_dot_dot)
{
	char	*result;

	result = canonicalize_absolute_path("/path/../to/dir", false);
	EXPECT_STREQ(result, "/to/dir");
	free(result);
}

// / が連続する
TEST(canonicalize_absolute_path, consecutive_slash)
{
	char	*result;

	result = canonicalize_absolute_path("/path//to/dir", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// 先頭に / が連続
TEST(canonicalize_absolute_path, consecutive_slash2)
{
	char	*result;

	result = canonicalize_absolute_path("//path//to/dir", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// 複合
TEST(canonicalize_absolute_path, complex)
{
	char	*result;

	result = canonicalize_absolute_path("//path/./../to/dir//", false);
	EXPECT_STREQ(result, "/to/dir");
	free(result);
}

// 絶対パスで空になる
TEST(canonicalize_absolute_path, be_empty)
{
	char	*result;

	result = canonicalize_absolute_path("/path/../", false);
	EXPECT_STREQ(result, "/");
	free(result);
}

// root から更に上に行く
TEST(canonicalize_absolute_path, go_up_to_root)
{
	char	*result;

	result = canonicalize_absolute_path("/..", false);
	EXPECT_STREQ(result, "/");
	free(result);
}

// 複数回 ..
TEST(canonicalize_absolute_path, multi_dot_dot)
{
	char	*result;

	result = canonicalize_absolute_path("/path/to/dir/../..", false);
	EXPECT_STREQ(result, "/path");
	free(result);
}

// 複数回 .. で / になる
TEST(canonicalize_absolute_path, multi_dot_dot2)
{
	char	*result;

	result = canonicalize_absolute_path("/path/to/dir/../../..", false);
	EXPECT_STREQ(result, "/");
	free(result);
}
