#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

extern "C" {
#include "builtins.h"
#include "context.h"
}

// オプションなし
TEST(builtins_echo, no_option) {
	testing::internal::CaptureStdout();
	const char *args[] = {"hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello world\n");
}

// オプションなし, 引数なし
TEST(builtins_echo, no_option_no_arg) {
	testing::internal::CaptureStdout();
	const char *args[] = {nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "\n");
}

// オプションなし, 空文字含む
TEST(builtins_echo, no_option_empty) {
	testing::internal::CaptureStdout();
	const char *args[] = {"", "hello", "", "world", "", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, " hello  world \n");
}

// オプションあり
TEST(builtins_echo, with_n_option) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-n", "hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello world");
}

// オプションあり, 引数なし
TEST(builtins_echo, with_n_option_no_arg) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-n", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "");
}

// オプションあり, 空文字含む
TEST(builtins_echo, with_n_option_empty) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-n", "", "hello", "", "world", "", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, " hello  world ");
}

// オプションの位置が違う
TEST(builtins_echo, wrong_option_position) {
	testing::internal::CaptureStdout();
	const char *args[] = {"hello", "-n", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello -n world\n");
}

// オプションっぽい文字列
TEST(builtins_echo, option_like_string) {
	testing::internal::CaptureStdout();
	const char *args[] = {"--n", "hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "--n hello world\n");
}

TEST(builtins_echo, option_like_string2) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-nhello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "-nhello world\n");
}

TEST(builtins_echo, option_like_string3) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-n ", "hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "-n  hello world\n");
}

// オプション複数
TEST(builtins_echo, multiple_options) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-n", "-n", "hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello world");
}

// nが複数
TEST(builtins_echo, multiple_n) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-nn", "-nnn", "hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "hello world");
}

// ハイフンだけ
TEST(builtins_echo, only_hyphen) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "-\n");
}

// -n以外
TEST(builtins_echo, not_n_option) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-a", "hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "-a hello world\n");
}

// -- あり
// echoでは特別扱いしない
TEST(builtins_echo, double_hyphen) {
	testing::internal::CaptureStdout();
	const char *args[] = {"--", "hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);

	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "-- hello world\n");
}

// -- -n
TEST(builtins_echo, double_hyphen_n_option) {
	testing::internal::CaptureStdout();
	const char *args[] = {"--", "-n", "hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);

	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "-- -n hello world\n");
}

// -n --
TEST(builtins_echo, n_option_double_hyphen) {
	testing::internal::CaptureStdout();
	const char *args[] = {"-n", "--", "hello", "world", nullptr};
	t_context ctx = {.shell_name = "minishell"};
	int ret = builtins_echo(&ctx, args);

	auto output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(ret, EXIT_SUCCESS);
	EXPECT_EQ(output, "-- hello world");
}
