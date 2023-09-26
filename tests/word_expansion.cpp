#include <gtest/gtest.h>
#include "utils/context.hpp"

extern "C" {
#include "word_expansion/word_expansion_internal.h"
#include "context.h"
#include "libft.h"
}

TEST(parameter, normal) {
	char *input = "$hello";
	char *expected = "world";
	t_context *ctx = Context({{"hello", "world"}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, alnum) {
	char *input = "$hello42";
	char *expected = "world42";
	t_context *ctx = Context({{"hello42", "world42"}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, multiple) {
	char *input = "-- $hello $world --";
	char *expected = "-- from 42 --";
	t_context *ctx = Context({{"hello", "from"}, {"world", "42"}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, not_found) {
	char *input = "$hello";
	char *expected = "";
	t_context *ctx = Context().getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, empty) {
	char *input = "$hello";
	char *expected = "";
	t_context *ctx = Context({{"hello", ""}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, no_vars) {
	char *input = "hello world";
	char *expected = "hello world";
	t_context *ctx = Context().getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, only_doller) {
	char *input = "$";
	char *expected = "$";
	t_context *ctx = Context().getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, illegal_name) {
	char *input = "$/42";
	char *expected = "$/42";
	t_context *ctx = Context().getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, whitespace_in_value) {
	char *input = "$hello";
	char *expected = "hello world";
	t_context *ctx = Context({{"hello", "hello world"}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, exit_status) {
	char *input = "$?";
	char *expected = "42";
	t_context *ctx = Context(42).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, with_double_quote)
{
	char *input = "\"$hello\"";
	char *expected = "\"world\"";
	t_context *ctx = Context({{"hello", "world"}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, with_multiple_double_quotes)
{
	char *input = "-- \"$hello from\" \"ecole $world\" --";
	char *expected = "-- \"greeting from\" \"ecole 42\" --";
	t_context *ctx = Context({{"hello", "greeting"}, {"world", "42"}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(paramteter, with_single_quote) {
	char *input = "'$hello'";
	char *expected = "'$hello'";
	t_context *ctx = Context({{"hello", "world"}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, with_multiple_single_quotes) {
	char *input = "-- '$hello from' 'ecole $world' --";
	char *expected = "-- '$hello from' 'ecole $world' --";
	t_context *ctx = Context({{"hello", "greeting"}, {"world", "42"}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}

TEST(parameter, with_multiple_quotes) {
	char *input = "-- '$hello from' \"ecole $world\" --";
	char *expected = "-- '$hello from' \"ecole 42\" --";
	t_context *ctx = Context({{"hello", "greeting"}, {"world", "42"}}).getCtx();
	char *result = expand_parameter(input, ctx);

	EXPECT_STREQ(expected, result);
}
