#include <gtest/gtest.h>

extern "C" {
#include "builtins.h"
}

class builtinsExitTest : public ::testing::Test {
protected:
	t_context ctx{};

	void SetUp() override {
		ctx = (t_context) {
			.shell_name = "minishell",
			.is_interactive = true
		};
	}
};

TEST_F(builtinsExitTest, normal) {
	const char *args[] = {"0", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 他の値
TEST_F(builtinsExitTest, other_value) {
	const char *args[] = {"42", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 正の符号あり
TEST_F(builtinsExitTest, positive_with_sign) {
	const char *args[] = {"+42", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 255より大きい
TEST_F(builtinsExitTest, greater_than_255) {
	const char *args[] = {"256", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

TEST_F(builtinsExitTest, greater_than_255_2) {
	const char *args[] = {"1000", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(232), "exit\n");
}

// 負の値
TEST_F(builtinsExitTest, negative) {
	const char *args[] = {"-1", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(255), "exit\n");
}

TEST_F(builtinsExitTest, negative_2) {
	const char *args[] = {"-42", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(214), "exit\n");
}

TEST_F(builtinsExitTest, negative_3) {
	const char *args[] = {"-1000", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(24), "exit\n");
}

// 引数なし
TEST_F(builtinsExitTest, no_arg) {
	const char *args[] = {nullptr};
	this->ctx.last_exit_status = 42;

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 引数がINT_MAX
TEST_F(builtinsExitTest, int_max) {
	const char *args[] = {"2147483647", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(255), "exit\n");
}

// 引数がINT_MIN
TEST_F(builtinsExitTest, int_min) {
	const char *args[] = {"-2147483648", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 引数がINT_MAXより大きい
TEST_F(builtinsExitTest, greater_than_int_max) {
	const char *args[] = {"2147483648", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 引数がINT_MINより小さい
TEST_F(builtinsExitTest, less_than_int_min) {
	const char *args[] = {"-2147483649", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(255), "exit\n");
}

// 引数がLONG_MAX
TEST_F(builtinsExitTest, long_max) {
	const char *args[] = {"9223372036854775807", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(255), "exit\n");
}

// 引数がLONG_MIN
TEST_F(builtinsExitTest, long_min) {
	const char *args[] = {"-9223372036854775808", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 引数がLONG_MAXより大きい
TEST_F(builtinsExitTest, greater_than_long_max) {
	const char *args[] = {"9223372036854775808", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: 9223372036854775808: numeric argument required\n");
}

// 引数がLONG_MINより小さい
TEST_F(builtinsExitTest, less_than_long_min) {
	const char *args[] = {"-9223372036854775809", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: -9223372036854775809: numeric argument required\n");
}

// 前後にスペース
TEST_F(builtinsExitTest, with_space) {
	const char *args[] = {" 42 ", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 前後にタブ
TEST_F(builtinsExitTest, with_tab) {
	const char *args[] = {"\t42\t", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 前後にスペース, 符号あり
TEST_F(builtinsExitTest, with_space_with_sign) {
	const char *args[] = {" +42 ", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 前後にスペース, 符号複数
TEST_F(builtinsExitTest, with_space_with_multiple_sign) {
	const char *args[] = {" +-42 ", nullptr};

	// 正規表現でマッチさせるので, +はエスケープする
	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit:  \\+-42 : numeric argument required\n");
}

// 前後にスペース, 符号あり, 0
TEST_F(builtinsExitTest, with_space_with_sign_zero) {
	const char *args[] = {" +0 ", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 0埋め
TEST_F(builtinsExitTest, zero_padding) {
	const char *args[] = {"00042", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 0埋め, 0
TEST_F(builtinsExitTest, zero_padding_zero) {
	const char *args[] = {"00000", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(0), "exit\n");
}

// 符号だけ
TEST_F(builtinsExitTest, only_sign) {
	const char *args[] = {"+", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: \\+: numeric argument required\n");
}

// 符号だけ
TEST_F(builtinsExitTest, only_sign_minus) {
	const char *args[] = {"-", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: -: numeric argument required\n");
}

// 符号だけ
TEST_F(builtinsExitTest, only_sign_plus_minus) {
	const char *args[] = {"+-", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: \\+-: numeric argument required\n");
}

// 数字以外を含む
TEST_F(builtinsExitTest, with_non_digit) {
	const char *args[] = {"42a", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: 42a: numeric argument required\n");
}

// 途中にスペース
TEST_F(builtinsExitTest, with_space_in_the_middle) {
	const char *args[] = {"4 2", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: 4 2: numeric argument required\n");
}

// 符号の後にスペース
TEST_F(builtinsExitTest, with_space_after_sign) {
	const char *args[] = {"+ 42", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: \\+ 42: numeric argument required\n");
}

// スペースを空けて複数の符号
TEST_F(builtinsExitTest, with_multiple_sign_with_space) {
	const char *args[] = {"+ -42", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: \\+ -42: numeric argument required\n");
}

// 有効の数字の後にスペースを空けて文字
TEST_F(builtinsExitTest, with_space_after_digit) {
	const char *args[] = {"42 a", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: 42 a: numeric argument required\n");
}

// 空文字
TEST_F(builtinsExitTest, empty) {
	const char *args[] = {"", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: : numeric argument required\n");
}

// 引数2つ, 最初が数字でない
TEST_F(builtinsExitTest, two_args_first_not_digit) {
	const char *args[] = {"a", "42", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(2),
				"exit\n"
				"minishell: exit: a: numeric argument required\n");
}

// 引数2つ, 最初が数字
TEST_F(builtinsExitTest, two_args_first_digit) {
	testing::internal::CaptureStderr();
	const char *args[] = {"42", "a", nullptr};
	this->ctx.last_exit_status = 42;
	int ret = builtins_exit(&this->ctx, args);

	EXPECT_EQ(ret, 42);
	EXPECT_STREQ(testing::internal::GetCapturedStderr().c_str(),
				 "exit\n"
				 "minishell: exit: too many arguments\n");
}

// 引数2つ, 最初が数字, 前回の終了ステータスが0
TEST_F(builtinsExitTest, two_args_first_digit_last_exit_status_zero) {
	testing::internal::CaptureStderr();
	const char *args[] = {"42", "a", nullptr};
	this->ctx.last_exit_status = 0;
	int ret = builtins_exit(&this->ctx, args);

	EXPECT_EQ(ret, 1);
	EXPECT_STREQ(testing::internal::GetCapturedStderr().c_str(),
				 "exit\n"
				 "minishell: exit: too many arguments\n");
}

// 引数2つ, 1つ目が "--"
TEST_F(builtinsExitTest, two_args_first_double_hyphen) {
	const char *args[] = {"--", "42", nullptr};

	EXPECT_EXIT(builtins_exit(&this->ctx, args), ::testing::ExitedWithCode(42), "exit\n");
}

// 最初でなければエラー
TEST_F(builtinsExitTest, two_args_not_first_double_hyphen) {
	testing::internal::CaptureStderr();
	const char *args[] = {"42", "--", nullptr};
	this->ctx.last_exit_status = 42;
	int ret = builtins_exit(&this->ctx, args);

	EXPECT_EQ(ret, 42);
	EXPECT_STREQ(testing::internal::GetCapturedStderr().c_str(),
				 "exit\n"
				 "minishell: exit: too many arguments\n");
}