#include <gtest/gtest.h>

extern "C" {
#include "builtins_internal.h"
}

TEST(get_next_option, normal) {
	char *arg = (char *) "-aabc";
	char *optstring = (char *) "abc";
	t_getopt_status ret;
	char option;

	init_get_next_option();
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_SUCCESS);
	EXPECT_EQ(option, 'a');
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_SUCCESS);
	EXPECT_EQ(option, 'a');
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_SUCCESS);
	EXPECT_EQ(option, 'b');
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_SUCCESS);
	EXPECT_EQ(option, 'c');
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_END_OF_ARG);
}

// オプションではない
TEST(get_next_option, not_option) {
	char *arg = (char *) "aabc";
	char *optstring = (char *) "abc";
	t_getopt_status ret;
	char option;

	init_get_next_option();
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_END_OF_OPTIONS);
}

// 空文字
TEST(get_next_option, not_option2) {
	char *arg = (char *) "";
	char *optstring = (char *) "abc";
	t_getopt_status ret;
	char option;

	init_get_next_option();
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_END_OF_OPTIONS);
}

// "-"
TEST(get_next_option, end_of_options) {
	char *arg = (char *) "-";
	char *optstring = (char *) "abc";
	t_getopt_status ret;
	char option;

	init_get_next_option();
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_END_OF_OPTIONS);
}

// "--"
TEST(get_next_option, end_of_options2) {
	char *arg = (char *) "--";
	char *optstring = (char *) "abc";
	t_getopt_status ret;
	char option;

	init_get_next_option();
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_END_OF_ARG);
}

// "--" から始まる文字列
TEST(get_next_option, illegal_option) {
	char *arg = (char *) "--abc";
	char *optstring = (char *) "abc";
	t_getopt_status ret;
	char option;

	init_get_next_option();
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_ILLEGAL);
}

// "---"
TEST(get_next_option, illegal_option2) {
	char *arg = (char *) "---";
	char *optstring = (char *) "abc";
	t_getopt_status ret;
	char option;

	init_get_next_option();
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_ILLEGAL);
}

// 最後まで読み込めるか
TEST(get_next_option, end_of_arg) {
	char *arg = (char *) "-xyz";
	char *optstring = (char *) "abc";
	t_getopt_status ret;
	char option;

	init_get_next_option();
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_ILLEGAL);
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_ILLEGAL);
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_ILLEGAL);
	ret = get_next_option(arg, optstring, &option);
	EXPECT_EQ(ret, OPT_END_OF_ARG);
}