#include <gtest/gtest.h>
extern "C" {
#include "variables.h"
#include "variables_internal.h"
}

// 普通のケース
TEST(parse_assignment, normal)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_SUCCESS);
	EXPECT_STREQ(result.name, "NAME");
	EXPECT_STREQ(result.value, "VALUE");
	EXPECT_EQ(result.operation, OP_SET);
}

// 加算代入
TEST(parse_assignment, append)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME+=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_SUCCESS);
	EXPECT_STREQ(result.name, "NAME");
	EXPECT_STREQ(result.value, "VALUE");
	EXPECT_EQ(result.operation, OP_APPEND);
}

// 無効な演算子
TEST(parse_assignment, invalid_operator)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME-=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}

// valueなし
TEST(parse_assignment, no_value)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME=");
	EXPECT_EQ(status, ASSIGN_PARSE_SUCCESS);
	EXPECT_STREQ(result.name, "NAME");
	EXPECT_STREQ(result.value, "");
	EXPECT_EQ(result.operation, OP_SET);
}

// valueなし, 加算代入
TEST(parse_assignment, no_value_append)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME+=");
	EXPECT_EQ(status, ASSIGN_PARSE_SUCCESS);
	EXPECT_STREQ(result.name, "NAME");
	EXPECT_STREQ(result.value, "");
	EXPECT_EQ(result.operation, OP_APPEND);
}

// nameだけ
TEST(parse_assignment, only_name)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME");
	EXPECT_EQ(status, ASSIGN_PARSE_ONLY_IDENTIFIER);
	EXPECT_STREQ(result.name, "NAME");
	EXPECT_STREQ(result.value, nullptr);
}

// =が2つ
TEST(parse_assignment, double_equal)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME=VALUE=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_SUCCESS);
	EXPECT_STREQ(result.name, "NAME");
	EXPECT_STREQ(result.value, "VALUE=VALUE");
}

// 空文字列
TEST(parse_assignment, empty)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}

// 最初が=
TEST(parse_assignment, equal_only)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}

// 最初が+=
TEST(parse_assignment, append_only)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "+=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}

// =の前後にスペース
TEST(parse_assignment, space_around_equal)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME = VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}

// +=の前後にスペース
TEST(parse_assignment, space_around_append)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME += VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}

// nameが数字から始まる
TEST(parse_assignment, number)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "123NAME");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}

// nameが数字から始まる, valueあり
TEST(parse_assignment, number_value)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "123NAME=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}

// nameがスペースを含む
TEST(parse_assignment, space)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME 1=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}

// アンダースコア含む
TEST(parse_assignment, underscore)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME_1=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_SUCCESS);
	EXPECT_STREQ(result.name, "NAME_1");
	EXPECT_STREQ(result.value, "VALUE");
	EXPECT_EQ(result.operation, OP_SET);
}

// ハイフン含む
TEST(parse_assignment, hyphen)
{
	t_parse_status status;
	t_parsed_assignment result;

	status = parse_assignment(&result, "NAME-1=VALUE");
	EXPECT_EQ(status, ASSIGN_PARSE_INVALID_IDENTIFIER);
	EXPECT_EQ(result.name, nullptr);
	EXPECT_EQ(result.value, nullptr);
}
