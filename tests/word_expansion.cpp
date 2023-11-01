/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:44:54 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/20 13:54:51 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "utils/context.hpp"
#include "utils/compare_list.hpp"

extern "C" {
#include "word_expansion/word_expansion_internal.h"
#include "context.h"
}

TEST(expand_parameters, normal)
{
	auto input = "'hello '$USER' 42'";
	auto ctx = Context({{"USER", "root"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"'hello 'root' 42'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, no_param)
{
	auto input = "'hello world'";
	auto ctx = Context({{"USER", "root"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"'hello world'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, expand_in_double_quotes)
{
	auto input = "\"hello $USER 42\"";
	auto ctx = Context({{"USER", "root"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"\"hello root 42\""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, multiple)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "1"}, {"b", "2"}, {"c", "3"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"123"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, undefined)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "1"}, {"c", "3"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"13"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, undefined2)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "1"}, {"b", "2"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"12"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, undefined3)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"b", "2"}, {"c", "3"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"23"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, undefined4)
{
	auto input = "$a$b$c";
	auto ctx = Context({}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, empty)
{
	auto input = "";
	auto ctx = Context({}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, empty2)
{
	auto input = "$a";
	auto ctx = Context({{"a", ""}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, single_quote)
{
	auto input = "'$a'";
	auto ctx = Context({}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"'$a'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, single_double)
{
	auto input = "'\"$a\"'";
	auto ctx = Context({}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"'\"$a\"'"};

	ASSERT_TRUE(compareStrList(result, expected));
}
 
TEST(expand_parameters, double_single)
{
	auto input = "\"'$a'\"";
	auto ctx = Context({{"a", "1"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"\"'1'\""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, normal)
{
	auto input = "$a";
	auto ctx = Context({{"a", "  hello  world  "}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	auto expected = {"hello", "world"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, multiple)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  hello  "}, {"b", "  world  "}, {"c", "  42  "}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	auto expected = {"hello", "world", "42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, empty)
{
	auto input = "$a";
	auto ctx = Context({{"a", ""}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char*> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, empty2)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", ""}, {"b", ""}, {"c", ""}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char*> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, mixed_empty)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"}, {"b", "  "}, {"c", "world"}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char*> expected = {"hello", "world"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, double_quote)
{
	auto input = "\"$a\"";
	auto ctx = Context({{"a", "  hello  world  "}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char*> expected = {"\"  hello  world  \""};

	ASSERT_TRUE(compareStrList(result, expected));
}
 

TEST(expand_word, normal)
{
	auto input = "$a";
	auto ctx = Context({{"a", "hello"}}).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"hello"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, multiple)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"}, {"b", "world"}, {"c", "42"}}).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"helloworld42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, empty)
{
	auto input = "$a";
	auto ctx = Context({{"a", ""}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, empty2)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", ""}, {"b", ""}, {"c", ""}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, mixed_empty)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"}, {"b", ""}, {"c", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined)
{
	auto input = "$a";
	auto ctx = Context({{"b", "hello"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined2)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"}, {"c", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined3)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"}, {"b", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined4)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"b", "hello"}, {"c", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined5)
{
	auto input = "$a$b$c";
	auto ctx = Context({}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined6)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", ""}, {"b", ""}, {"c", ""}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined7)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"}, {"b", ""}, {"c", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space)
{
	auto input = "$a";
	auto ctx = Context({{"a", "  hello  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"hello"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space2)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  hello  "}, {"b", "  world  "}, {"c", "  42  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"hello", "world", "42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space3)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  hello  "}, {"b", "  "}, {"c", "  world  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"hello", "world"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space4)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  "}, {"b", "  world  "}, {"c", "  42  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"world", "42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space5)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  hello  "}, {"b", "  "}, {"c", "  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"hello"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space6)
{
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  "}, {"b", "  "}, {"c", "  42  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, single_quote)
{
	auto input = "'$a'";
	auto ctx = Context({}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"$a"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, double_quote)
{
	auto input = "\"$a\"";
	auto ctx = Context({{"a", "  hello  world  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"  hello  world  "};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, single_double)
{
	auto input = "'\"$a\"'";
	auto ctx = Context({}).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"\"$a\""};

	ASSERT_TRUE(compareStrList(result, expected));
}
 
TEST(expand_word, double_single)
{
	auto input = "\"'$a'\"";
	auto ctx = Context({{"a", "1"}}).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"'1'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, exit_status) {
	auto input = "$?";
	auto ctx = Context(42).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"42"};

	ASSERT_TRUE(compareStrList(result, expected));
}