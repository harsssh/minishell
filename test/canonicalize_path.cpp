#include <gtest/gtest.h>
extern "C" {
#include "cd/cd_internal.h"
}

// 正規化済みのパス
TEST(canonicalize_path, normal)
{
	char	*result;

	result = canonicalize_path("/path/to/dir", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// 相対パス
TEST(canonicalize_path, normal1)
{
	char	*result;

	result = canonicalize_path("path/to/dir", false);
	EXPECT_STREQ(result, "path/to/dir");
	free(result);
}

// パスの最後が / で終わる
TEST(canonicalize_path, normal2)
{
	char	*result;

	result = canonicalize_path("/path/to/dir/", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// ./ を含む
TEST(canonicalize_path, normal3)
{
	char	*result;

	result = canonicalize_path("/path/./to/dir", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// ../ を含む
TEST(canonicalize_path, normal4)
{
	char	*result;

	result = canonicalize_path("/path/../to/dir", false);
	EXPECT_STREQ(result, "/to/dir");
	free(result);
}

// / が連続する
TEST(canonicalize_path, normal5)
{
	char	*result;

	result = canonicalize_path("/path//to/dir", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// 先頭に / が連続
TEST(canonicalize_path, normal5_1)
{
	char	*result;

	result = canonicalize_path("//path//to/dir", false);
	EXPECT_STREQ(result, "/path/to/dir");
	free(result);
}

// 複合
TEST(canonicalize_path, normal6)
{
	char	*result;

	result = canonicalize_path("//path/./../to/dir//", false);
	EXPECT_STREQ(result, "/to/dir");
	free(result);
}

// 絶対パスで空になる
TEST(canonicalize_path, normal6_1)
{
	char	*result;

	result = canonicalize_path("/path/../", false);
	EXPECT_STREQ(result, "/");
	free(result);
}

// root から更に上に行く
TEST(canonicalize_path, normal7)
{
	char	*result;

	result = canonicalize_path("/..", false);
	EXPECT_STREQ(result, "/");
	free(result);
}

// 相対パスで空になる
TEST(canonicalize_path, normal8)
{
	char	*result;

	result = canonicalize_path("path/../", false);
	EXPECT_STREQ(result, ".");
	free(result);
}

// 相対パスで上に行き過ぎる
TEST(canonicalize_path, normal9)
{
	char	*result;

	result = canonicalize_path("path/../../../", false);
	EXPECT_STREQ(result, "../..");
	free(result);
}

// ./ から始まる
TEST(canonicalize_path, normal10)
{
	char	*result;

	result = canonicalize_path("./path/to/dir", false);
	EXPECT_STREQ(result, "path/to/dir");
	free(result);
}

// ../ から始まる
TEST(canonicalize_path, normal11)
{
	char	*result;

	result = canonicalize_path("../path/to/dir", false);
	EXPECT_STREQ(result, "../path/to/dir");
	free(result);
}

// ./ から始まる空のパス
TEST(canonicalize_path, normal12)
{
	char	*result;

	result = canonicalize_path("./path/../", false);
	EXPECT_STREQ(result, ".");
	free(result);
}

// 空文字
TEST(canonicalize_path, normal13)
{
	char	*result;

	result = canonicalize_path("", false);
	EXPECT_STREQ(result, ".");
	free(result);
}

// .. だけ
TEST(canonicalize_path, normal14)
{
	char	*result;

	result = canonicalize_path("..", false);
	EXPECT_STREQ(result, "..");
	free(result);
}

// 最後が . で / なし
TEST(canonicalize_path, normal15)
{
	char	*result;

	result = canonicalize_path("path/to/dir/.", false);
	EXPECT_STREQ(result, "path/to/dir");
	free(result);
}

// 最後が .. で / なし
TEST(canonicalize_path, normal16)
{
	char	*result;

	result = canonicalize_path("path/to/dir/..", false);
	EXPECT_STREQ(result, "path/to");
	free(result);
}

// 複数回 ..
TEST(canonicalize_path, normal17)
{
	char	*result;

	result = canonicalize_path("/path/to/dir/../..", false);
	EXPECT_STREQ(result, "/path");
	free(result);
}

// 複数回 .. で / になる
TEST(canonicalize_path, normal18)
{
	char	*result;

	result = canonicalize_path("/path/to/dir/../../..", false);
	EXPECT_STREQ(result, "/");
	free(result);
}

// 複数回 .. で . になる 
TEST(canonicalize_path, normal19)
{
	char	*result;

	result = canonicalize_path("path/to/dir/../../..", false);
	EXPECT_STREQ(result, ".");
	free(result);
}