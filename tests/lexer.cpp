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

// スペースなし
TEST(lexer, no_space)
{
	char	*input = "ls|ls|ls";
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

// quoteをネスト
TEST(lexer, quote_nest)
{
	char	*input = "echo \"'''42'''\"";
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
			EXPECT_STREQ(token->literal, "\"'''42'''\"");
		}
		cnt++;
	});
}

// quoted文字列の連接
TEST(lexer, quote_concat)
{
	char	*input = "echo \"42\"\"42\"";
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
			EXPECT_STREQ(token->literal, "\"42\"\"42\"");
		}
		cnt++;
	});
}

// 変数いっぱい
TEST(lexer, variables)
{
	char	*input = "echo $A$B$C$D";
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
			EXPECT_STREQ(token->literal, "$A$B$C$D");
		}
		cnt++;
	});
}

// 環境変数をquoteしたり, しなかったり
TEST(lexer, quote_not_quote)
{
	char	*input = "echo $A \"$B\" '$C' $D";
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
			EXPECT_STREQ(token->literal, "$A");
		} else if (cnt == 2) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "\"$B\"");
		} else if (cnt == 3) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "'$C'");
		} else if (cnt == 4) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "$D");
		}
		cnt++;
	});
}

// exportコマンド
TEST(lexer, export)
{
	char	*input = "export A=1 B=2";
	auto	result = tokenize(input);

	EXPECT_NE(result, nullptr);
	ft_list_iter(result, [](void *data) {
		t_token	*token = (t_token *)data;
		static int cnt = 0;

		if (cnt == 0) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "export");
		} else if (cnt == 1) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "A=1");
		} else if (cnt == 2) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "B=2");
		}
		cnt++;
	});
}

// redirectとpipe
TEST(lexer, redirect_pipe)
{
	char	*input = "cat > file1 | cat < file2 | cat >> file3 | cat << EOF";
	auto	result = tokenize(input);

	EXPECT_NE(result, nullptr);
	ft_list_iter(result, [](void *data) {
		t_token	*token = (t_token *)data;
		static int cnt = 0;

		if (cnt % 2) {
			EXPECT_EQ(token->type, TK_PIPE);
			EXPECT_STREQ(token->literal, "|");
		} else {
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
				EXPECT_EQ(token->type, TK_WORD);
				EXPECT_STREQ(token->literal, "cat");
			} else if (cnt == 4) {
				EXPECT_EQ(token->type, TK_REDIRECT_OUT);
				EXPECT_STREQ(token->literal, "<");
			} else if (cnt == 5) {
				EXPECT_EQ(token->type, TK_WORD);
				EXPECT_STREQ(token->literal, "file2");
			} else if (cnt == 6) {
				EXPECT_EQ(token->type, TK_WORD);
				EXPECT_STREQ(token->literal, "cat");
			} else if (cnt == 7) {
				EXPECT_EQ(token->type, TK_REDIRECT_APPEND);
				EXPECT_STREQ(token->literal, ">>");
			} else if (cnt == 8) {
				EXPECT_EQ(token->type, TK_WORD);
				EXPECT_STREQ(token->literal, "file3");
			} else if (cnt == 9) {
				EXPECT_EQ(token->type, TK_WORD);
				EXPECT_STREQ(token->literal, "cat");
			} else if (cnt == 10) {
				EXPECT_EQ(token->type, TK_REDIRECT_HERE_DOC);
				EXPECT_STREQ(token->literal, "<<");
			} else if (cnt == 11) {
				EXPECT_EQ(token->type, TK_WORD);
				EXPECT_STREQ(token->literal, "EOF");
			}
		}
		cnt++;
	});
}

// heredoc, delimiterに環境変数
TEST(lexer, heredoc)
{
	char	*input = "cat << $DELIMITER";
	auto	result = tokenize(input);

	EXPECT_NE(result, nullptr);
	ft_list_iter(result, [](void *data) {
		t_token	*token = (t_token *)data;
		static int cnt = 0;

		if (cnt == 0) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "cat");
		} else if (cnt == 1) {
			EXPECT_EQ(token->type, TK_REDIRECT_HERE_DOC);
			EXPECT_STREQ(token->literal, "<<");
		} else if (cnt == 2) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "$DELIMITER");
		}
		cnt++;
	});
}

// heredoc, delimiterがquoted
TEST(lexer, heredoc_quoted)
{
	char	*input = "cat << 'DELIMITER'";
	auto	result = tokenize(input);

	EXPECT_NE(result, nullptr);
	ft_list_iter(result, [](void *data) {
		t_token	*token = (t_token *)data;
		static int cnt = 0;

		if (cnt == 0) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "cat");
		} else if (cnt == 1) {
			EXPECT_EQ(token->type, TK_REDIRECT_HERE_DOC);
			EXPECT_STREQ(token->literal, "<<");
		} else if (cnt == 2) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "'DELIMITER'");
		}
		cnt++;
	});
}

// pipe, redirect, and/or 全部入りで, スペース省略
TEST(lexer, mix_omit_space)
{
	char	*input = "echo \"$A\"|cat>file2|cat&&cat||cat";
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
			EXPECT_STREQ(token->literal, "\"$A\"");
		} else if (cnt == 2) {
			EXPECT_EQ(token->type, TK_PIPE);
			EXPECT_STREQ(token->literal, "|");
		} else if (cnt == 3) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "cat");
		} else if (cnt == 4) {
			EXPECT_EQ(token->type, TK_REDIRECT_OUT);
			EXPECT_STREQ(token->literal, ">");
		} else if (cnt == 5) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "file2");
		} else if (cnt == 6) {
			EXPECT_EQ(token->type, TK_PIPE);
			EXPECT_STREQ(token->literal, "|");
		} else if (cnt == 7) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "cat");
		} else if (cnt == 8) {
			EXPECT_EQ(token->type, TK_AND);
			EXPECT_STREQ(token->literal, "&&");
		} else if (cnt == 9) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "cat");
		} else if (cnt == 10) {
			EXPECT_EQ(token->type, TK_OR);
			EXPECT_STREQ(token->literal, "||");
		} else if (cnt == 11) {
			EXPECT_EQ(token->type, TK_WORD);
			EXPECT_STREQ(token->literal, "cat");
		}
		cnt++;
	});
}
