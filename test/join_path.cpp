#include <gtest/gtest.h>
extern "C" {
#include "cd/cd_internal.h"
}

TEST(join_path, normal)
{
	char	*result;

	result = join_path("/home", "user");
	EXPECT_STREQ(result, "/home/user");
	free(result);
}

TEST(join_path, normal2)
{
	char	*result;

	result = join_path("/home", "user/Documents");
	EXPECT_STREQ(result, "/home/user/Documents");
	free(result);
}

// baseが / で終わる
TEST(join_path, normal3)
{
	char	*result;

	result = join_path("/home/", "user");
	EXPECT_STREQ(result, "/home/user");
	free(result);
}

// base="/"
TEST(join_path, normal4)
{
	char	*result;

	result = join_path("/", "home");
	EXPECT_STREQ(result, "/home");
	free(result);
}

// relpathが . で始まる
TEST(join_path, normal5)
{
	char	*result;

	result = join_path("/home", "./user");
	EXPECT_STREQ(result, "/home/./user");
	free(result);
}

// relpathが .. で始まる
TEST(join_path, normal6)
{
	char	*result;

	result = join_path("/home", "../user");
	EXPECT_STREQ(result, "/home/../user");
	free(result);
}

// baseが空
TEST(join_path, normal7)
{
	char	*result;

	result = join_path("", "home");
	EXPECT_STREQ(result, "home");
	free(result);
}

// relpathが空
TEST(join_path, normal8)
{
	char	*result;

	result = join_path("/home", "");
	EXPECT_STREQ(result, "/home");
	free(result);
}

// 両方空
TEST(join_path, normal9)
{
	char	*result;

	result = join_path("", "");
	EXPECT_STREQ(result, "");
	free(result);
}
