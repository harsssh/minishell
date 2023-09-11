#include <gtest/gtest.h>

extern "C" {
#include "builtins_internal.h"
}

TEST(get_next_option, normal) {
	char *arg = (char *) "-aabc";
	char *optstring = (char *) "abc";
	t_get_opt_status ret;

	init_get_next_option();
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, 'a');
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, 'a');
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, 'b');
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, 'c');
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, END_OF_ARG);
}

// オプションではない
TEST(get_next_option, not_option) {
	char *arg = (char *) "aabc";
	char *optstring = (char *) "abc";
	t_get_opt_status ret;

	init_get_next_option();
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, END_OF_OPTIONS);
}

// 空文字
TEST(get_next_option, not_option2) {
	char *arg = (char *) "";
	char *optstring = (char *) "abc";
	t_get_opt_status ret;

	init_get_next_option();
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, END_OF_OPTIONS);
}

// "-"
TEST(get_next_option, end_of_options) {
	char *arg = (char *) "-";
	char *optstring = (char *) "abc";
	t_get_opt_status ret;

	init_get_next_option();
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, END_OF_ARG);
}

// "--"
TEST(get_next_option, end_of_options2) {
	char *arg = (char *) "--";
	char *optstring = (char *) "abc";
	t_get_opt_status ret;

	init_get_next_option();
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, END_OF_OPTIONS);
}

// "--" から始まる文字列
TEST(get_next_option, illegal_option) {
	char *arg = (char *) "--abc";
	char *optstring = (char *) "abc";
	t_get_opt_status ret;

	init_get_next_option();
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, ILLEGAL_OPTION);
}

// "---"
TEST(get_next_option, illegal_option2) {
	char *arg = (char *) "---";
	char *optstring = (char *) "abc";
	t_get_opt_status ret;

	init_get_next_option();
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, ILLEGAL_OPTION);
}

// 最後まで読み込めるか
TEST(get_next_option, end_of_arg) {
	char *arg = (char *) "-xyz";
	char *optstring = (char *) "abc";
	t_get_opt_status ret;

	init_get_next_option();
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, ILLEGAL_OPTION);
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, ILLEGAL_OPTION);
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, ILLEGAL_OPTION);
	ret = get_next_option(arg, optstring);
	EXPECT_EQ(ret, END_OF_ARG);
}