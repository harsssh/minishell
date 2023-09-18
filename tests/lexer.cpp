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
