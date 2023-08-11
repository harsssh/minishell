#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

extern "C" {
#include "builtin.h"
}

// オプションなし
TEST(builtin_echo, no_option) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "hello", "world"};
	int argc = 3;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello world\n");
}

// オプションなし, 引数なし
TEST(builtin_echo, no_option_no_arg) {
	testing::internal::CaptureStdout();
	char *argv[] = {"echo"};
	int argc = 1;
	int ret = builtin_echo(argc, argv);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "\n");
}

// オプションなし, 空文字含む
TEST(builtin_echo, no_option_empty) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "", "hello", "", "world", ""};
	int argc = 6;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, " hello  world \n");
}

// オプションあり
TEST(builtin_echo, with_n_option) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "-n", "hello", "world"};
	int argc = 4;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello world");
}

// オプションあり, 引数なし
TEST(builtin_echo, with_n_option_no_arg) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "-n"};
	int argc = 2;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "");
}

// オプションあり, 空文字含む
TEST(builtin_echo, with_n_option_empty) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "-n", "", "hello", "", "world", ""};
	int argc = 7;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, " hello  world ");
}

// オプションの位置が違う
TEST(builtin_echo, wrong_option_position) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "hello", "-n", "world"};
	int argc = 4;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello -n world\n");
}

// オプションっぽい文字列
TEST(builtin_echo, option_like_string) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "--n", "hello", "world"};
	int argc = 4;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "--n hello world\n");
}

TEST(builtin_echo, option_like_string2) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "-nhello", "world"};
	int argc = 3;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "-nhello world\n");
}

TEST(builtin_echo, option_like_string3) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "-n ", "hello", "world"};
	int argc = 4;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "-n  hello world\n");
}

// オプション複数
TEST(builtin_echo, multiple_options) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "-n", "-n", "hello", "world"};
	int argc = 5;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello world");
}

// nが複数
TEST(builtin_echo, multiple_n) {
	testing::internal::CaptureStdout();
	const char *argv[] = {"echo", "-nn", "-nnn", "hello", "world"};
	int argc = 5;
	int ret = builtin_echo(argc, const_cast<char **>(argv));
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello world");
}

