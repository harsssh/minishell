#include <gtest/gtest.h>

extern "C" {
#include "builtin.h"
}

class BuiltinExitTest : public ::testing::Test {
protected:
	t_context ctx{};

	void SetUp() override {
		ctx = (t_context) {.shell_name = "minishell", .last_exit_status = 0};
	}
};

TEST_F(BuiltinExitTest, normal) {
	char *args[] = {"0", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 他の値
TEST_F(BuiltinExitTest, other_value) {
	char *args[] = {"42", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 正の符号あり
TEST_F(BuiltinExitTest, positive_with_sign) {
	char *args[] = {"+42", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 255より大きい
TEST_F(BuiltinExitTest, greater_than_255) {
	char *args[] = {"256", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

TEST_F(BuiltinExitTest, greater_than_255_2) {
	char *args[] = {"1000", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(232), "exit\n");
}

// 負の値
TEST_F(BuiltinExitTest, negative) {
	char *args[] = {"-1", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(255), "exit\n");
}

TEST_F(BuiltinExitTest, negative_2) {
	char *args[] = {"-42", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(214), "exit\n");
}

TEST_F(BuiltinExitTest, negative_3) {
	char *args[] = {"-1000", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(24), "exit\n");
}

// 引数なし
TEST_F(BuiltinExitTest, no_arg) {
	char *args[] = {nullptr};
	this->ctx.last_exit_status = 42;

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 引数がINT_MAX
TEST_F(BuiltinExitTest, int_max) {
	char *args[] = {"2147483647", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(255), "exit\n");
}

// 引数がINT_MIN
TEST_F(BuiltinExitTest, int_min) {
	char *args[] = {"-2147483648", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 引数がINT_MAXより大きい
TEST_F(BuiltinExitTest, greater_than_int_max) {
	char *args[] = {"2147483648", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 引数がINT_MINより小さい
TEST_F(BuiltinExitTest, less_than_int_min) {
	char *args[] = {"-2147483649", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(255), "exit\n");
}

// 引数がLONG_MAX
TEST_F(BuiltinExitTest, long_max) {
	char *args[] = {"9223372036854775807", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(255), "exit\n");
}

// 引数がLONG_MIN
TEST_F(BuiltinExitTest, long_min) {
	char *args[] = {"-9223372036854775808", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 引数がLONG_MAXより大きい
TEST_F(BuiltinExitTest, greater_than_long_max) {
	char *args[] = {"9223372036854775808", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: 9223372036854775808: numeric argument required\n");
}

// 引数がLONG_MINより小さい
TEST_F(BuiltinExitTest, less_than_long_min) {
	char *args[] = {"-9223372036854775809", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: -9223372036854775809: numeric argument required\n");
}

// 前後にスペース
TEST_F(BuiltinExitTest, with_space) {
	char *args[] = {" 42 ", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 前後にタブ
TEST_F(BuiltinExitTest, with_tab) {
	char *args[] = {"\t42\t", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 前後にスペース, 符号あり
TEST_F(BuiltinExitTest, with_space_with_sign) {
	char *args[] = {" +42 ", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 前後にスペース, 符号複数
TEST_F(BuiltinExitTest, with_space_with_multiple_sign) {
	char *args[] = {" +-42 ", nullptr};

	// 正規表現でマッチさせるので, +はエスケープする
	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit:  \\+-42 : numeric argument required\n");
}

// 前後にスペース, 符号あり, 0
TEST_F(BuiltinExitTest, with_space_with_sign_zero) {
	char *args[] = {" +0 ", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 0埋め
TEST_F(BuiltinExitTest, zero_padding) {
	char *args[] = {"00042", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 0埋め, 0
TEST_F(BuiltinExitTest, zero_padding_zero) {
	char *args[] = {"00000", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 符号だけ
TEST_F(BuiltinExitTest, only_sign) {
	char *args[] = {"+", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: \\+: numeric argument required\n");
}

// 符号だけ
TEST_F(BuiltinExitTest, only_sign_minus) {
	char *args[] = {"-", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: -: numeric argument required\n");
}

// 符号だけ
TEST_F(BuiltinExitTest, only_sign_plus_minus) {
	char *args[] = {"+-", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: \\+-: numeric argument required\n");
}

// 数字以外を含む
TEST_F(BuiltinExitTest, with_non_digit) {
	char *args[] = {"42a", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: 42a: numeric argument required\n");
}

// 途中にスペース
TEST_F(BuiltinExitTest, with_space_in_the_middle) {
	char *args[] = {"4 2", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: 4 2: numeric argument required\n");
}

// 符号の後にスペース
TEST_F(BuiltinExitTest, with_space_after_sign) {
	char *args[] = {"+ 42", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: \\+ 42: numeric argument required\n");
}

// スペースを空けて複数の符号
TEST_F(BuiltinExitTest, with_multiple_sign_with_space) {
	char *args[] = {"+ -42", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: \\+ -42: numeric argument required\n");
}

// 有効の数字の後にスペースを空けて文字
TEST_F(BuiltinExitTest, with_space_after_digit) {
	char *args[] = {"42 a", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: 42 a: numeric argument required\n");
}

// 空文字
TEST_F(BuiltinExitTest, empty) {
	char *args[] = {"", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: : numeric argument required\n");
}

// 引数2つ, 最初が数字でない
TEST_F(BuiltinExitTest, two_args_first_not_digit) {
	char *args[] = {"a", "42", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: a: numeric argument required\n");
}

// 引数2つ, 最初が数字
TEST_F(BuiltinExitTest, two_args_first_digit) {
	testing::internal::CaptureStderr();
	char *args[] = {"42", "a", nullptr};
	this->ctx.last_exit_status = 42;
	int ret = builtin_exit(&this->ctx, args);

	EXPECT_EQ(ret, 42);
	EXPECT_STREQ(testing::internal::GetCapturedStderr().c_str(),
				 "exit\n"
				 "minishell: exit: too many arguments\n");
}

// 引数2つ, 最初が数字, 前回の終了ステータスが0
TEST_F(BuiltinExitTest, two_args_first_digit_last_exit_status_zero) {
	testing::internal::CaptureStderr();
	char *args[] = {"42", "a", nullptr};
	this->ctx.last_exit_status = 0;
	int ret = builtin_exit(&this->ctx, args);

	EXPECT_EQ(ret, 1);
	EXPECT_STREQ(testing::internal::GetCapturedStderr().c_str(),
				 "exit\n"
				 "minishell: exit: too many arguments\n");
}

// 引数2つ, 1つ目が "--"
TEST_F(BuiltinExitTest, two_args_first_double_hyphen) {
	char *args[] = {"--", "42", nullptr};

	EXPECT_EXIT(builtin_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 最初でなければエラー
TEST_F(BuiltinExitTest, two_args_not_first_double_hyphen) {
	testing::internal::CaptureStderr();
	char *args[] = {"42", "--", nullptr};
	this->ctx.last_exit_status = 42;
	int ret = builtin_exit(&this->ctx, args);

	EXPECT_EQ(ret, 42);
	EXPECT_STREQ(testing::internal::GetCapturedStderr().c_str(),
				 "exit\n"
				 "minishell: exit: too many arguments\n");
}