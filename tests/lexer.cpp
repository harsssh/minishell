#include <gtest/gtest.h>
extern "C" {
#include "lexer_internal.h"
#include "token.h"
#include "lexer.h"
}

TEST(lexer, normal)
{
	char	*input = "ls";
	auto	result = tokenize(input);

	EXPECT_NE(result, nullptr);
	ft_list_iter(result, [](void *data) {
		t_token	*token = (t_token *)data;

		EXPECT_EQ(token->type, TK_WORD);
		EXPECT_STREQ(token->literal, "ls");
	});
}

TEST(lexer, pipe)
{
	char	*input = "ls | ls | ls";
	auto	result = tokenize(input);

	EXPECT_NE(result, nullptr);
	ft_list_iter(result, [](void *data) {
		t_token	*token = (t_token *)data;
		static int cnt = 0;

		if (cnt % 2) {
			EXPECT_EQ(token->type, TK_PIPE);
			EXPECT_STREQ(token->literal, "|");
		} else {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "ls");
		}
		cnt++;
	});
}

TEST(lexer, redirect)
{
	char	*input = "cat > file1 < file2 >> file3";
	auto	result = tokenize(input);

	EXPECT_NE(result, nullptr);
	ft_list_iter(result, [](void *data) {
		t_token	*token = (t_token *)data;
		static int cnt = 0;

		if (cnt == 0) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "cat");
		} else if (cnt == 1) {
			EXPECT_EQ(token->type, TK_REDIRECT_OUT);
			EXPECT_STREQ(token->literal, ">");
		} else if (cnt == 2) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "file1");
		} else if (cnt == 3) {
			EXPECT_EQ(token->type, TK_REDIRECT_IN);
			EXPECT_STREQ(token->literal, "<");
		} else if (cnt == 4) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "file2");
		} else if (cnt == 5) {
			EXPECT_EQ(token->type, TK_REDIRECT_APPEND);
			EXPECT_STREQ(token->literal, ">>");
		} else if (cnt == 6) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "file3");
		}
		cnt++;
	});
}

TEST(lexer, and_or)
{
	char	*input = "./cmd1 && cmd2 || /bin/cmd3";
	auto	result = tokenize(input);

	EXPECT_NE(result, nullptr);
	ft_list_iter(result, [](void *data) {
		t_token	*token = (t_token *)data;
		static int cnt = 0;

		if (cnt == 0) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "./cmd1");
		} else if (cnt == 1) {
			EXPECT_EQ(token->type, TK_AND);
			EXPECT_STREQ(token->literal, "&&");
		} else if (cnt == 2) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "cmd2");
		} else if (cnt == 3) {
			EXPECT_EQ(token->type, TK_OR);
			EXPECT_STREQ(token->literal, "||");
		} else if (cnt == 4) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "/bin/cmd3");
		}
		cnt++;
	});
}

TEST(lexer, quote)
{
	char	*input = "echo \"hello world\" 'hello world'";
	auto	result = tokenize(input);

	EXPECT_NE(result, nullptr);
	ft_list_iter(result, [](void *data) {
		t_token	*token = (t_token *)data;
		static int cnt = 0;

		if (cnt == 0) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "echo");
		} else if (cnt == 1) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "\"hello world\"");
		} else if (cnt == 2) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "'hello world'");
		}
		cnt++;
	});
}

TEST(lexer, error_quote)
{
	char	*input = "echo \"hello world\" 'hello world' \"hello world";
	auto	result = tokenize(input);

	EXPECT_EQ(result, nullptr);
}

TEST(lexer, error_quote2)
{
	char	*input = "echo 'hello world\"";
	auto	result = tokenize(input);

	EXPECT_EQ(result, nullptr);
}
