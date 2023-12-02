#include <gtest/gtest.h>
#include "utils/compare_list.hpp"
extern "C" {
#include "lexer_internal.h"
#include "token.h"
#include "lexer.h"
#include "utils/context.hpp"
}

TEST(lexer, normal)
{
	char	*input = "ls";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result, {{TK_WORD, "ls"}, {TK_EOF, ""}}));
}

TEST(lexer, pipe)
{
	char	*input = "ls | ls | ls";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "ls"},
		{TK_PIPE, "|"},
		{TK_WORD, "ls"},
		{TK_PIPE, "|"},
		{TK_WORD, "ls"},
		{TK_EOF, ""}}));
}

TEST(lexer, redirect)
{
	char	*input = "cat > file1 < file2 >> file3";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "cat"},
		{TK_REDIRECT_OUT, ">"},
		{TK_WORD, "file1"},
		{TK_REDIRECT_IN, "<"},
		{TK_WORD, "file2"},
		{TK_REDIRECT_APPEND, ">>"},
		{TK_WORD, "file3"},
		{TK_EOF, ""}}));
}

TEST(lexer, and_or)
{
	char	*input = "./cmd1 && cmd2 || /bin/cmd3";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "./cmd1"},
		{TK_AND, "&&"},
		{TK_WORD, "cmd2"},
		{TK_OR, "||"},
		{TK_WORD, "/bin/cmd3"},
		{TK_EOF, ""}}));
}

TEST(lexer, quote)
{
	char	*input = "echo \"hello world\" 'hello world'";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "echo"},
		{TK_WORD, "\"hello world\""},
		{TK_WORD, "'hello world'"},
		{TK_EOF, ""}}));
}

TEST(lexer, error_quote)
{
	char	*input = "echo \"hello world\" 'hello world' \"hello world";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_EQ(result, nullptr);
}

TEST(lexer, error_quote2)
{
	char	*input = "echo 'hello world\"";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_EQ(result, nullptr);
}

// スペースなし
TEST(lexer, no_space)
{
	char	*input = "ls|ls|ls";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "ls"},
		{TK_PIPE, "|"},
		{TK_WORD, "ls"},
		{TK_PIPE, "|"},
		{TK_WORD, "ls"},
		{TK_EOF, ""}}));
}

// quoteをネスト
TEST(lexer, quote_nest)
{
	char	*input = "echo \"'''42'''\"";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "echo"},
		{TK_WORD, "\"'''42'''\""},
		{TK_EOF, ""}}));
}

// quoted文字列の連接
TEST(lexer, quote_concat)
{
	char	*input = "echo \"42\"\"42\"";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "echo"},
		{TK_WORD, "\"42\"\"42\""},
		{TK_EOF, ""}}));
}

// 変数いっぱい
TEST(lexer, variables)
{
	char	*input = "echo $A$B$C$D";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "echo"},
		{TK_WORD, "$A$B$C$D"},
		{TK_EOF, ""}}));
}

// 環境変数をquoteしたり, しなかったり
TEST(lexer, quote_not_quote)
{
	char	*input = "echo $A \"$B\" '$C' $D";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "echo"},
		{TK_WORD, "$A"},
		{TK_WORD, "\"$B\""},
		{TK_WORD, "'$C'"},
		{TK_WORD, "$D"},
		{TK_EOF, ""}}));
}

// exportコマンド
TEST(lexer, export)
{
	char	*input = "export A=1 B=2";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "export"},
		{TK_WORD, "A=1"},
		{TK_WORD, "B=2"},
		{TK_EOF, ""}}));
}

// redirectとpipe
TEST(lexer, redirect_pipe)
{
	char	*input = "cat > file1 | cat < file2 | cat >> file3 | cat << EOF";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "cat"},
		{TK_REDIRECT_OUT, ">"},
		{TK_WORD, "file1"},
		{TK_PIPE, "|"},
		{TK_WORD, "cat"},
		{TK_REDIRECT_IN, "<"},
		{TK_WORD, "file2"},
		{TK_PIPE, "|"},
		{TK_WORD, "cat"},
		{TK_REDIRECT_APPEND, ">>"},
		{TK_WORD, "file3"},
		{TK_PIPE, "|"},
		{TK_WORD, "cat"},
		{TK_REDIRECT_HERE_DOC, "<<"},
		{TK_WORD, "EOF"},
		{TK_EOF, ""}}));
}

// heredoc, delimiterに環境変数
TEST(lexer, heredoc)
{
	char	*input = "cat << $DELIMITER";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "cat"},
		{TK_REDIRECT_HERE_DOC, "<<"},
		{TK_WORD, "$DELIMITER"},
		{TK_EOF, ""}}));
}

// heredoc, delimiterがquoted
TEST(lexer, heredoc_quoted)
{
	char	*input = "cat << ' DELIMITER '";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "cat"},
		{TK_REDIRECT_HERE_DOC, "<<"},
		{TK_WORD, "' DELIMITER '"},
		{TK_EOF, ""}}));
}

// pipe, redirect, and/or 全部入りで, スペース省略
TEST(lexer, mix_omit_space)
{
	char	*input = "echo \"$A\"|cat>file2|cat&&cat||cat";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "echo"},
		{TK_WORD, "\"$A\""},
		{TK_PIPE, "|"},
		{TK_WORD, "cat"},
		{TK_REDIRECT_OUT, ">"},
		{TK_WORD, "file2"},
		{TK_PIPE, "|"},
		{TK_WORD, "cat"},
		{TK_AND, "&&"},
		{TK_WORD, "cat"},
		{TK_OR, "||"},
		{TK_WORD, "cat"},
		{TK_EOF, ""}}));
}

TEST(lexer, empty)
{
	char *input = "";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result, {{TK_EOF, ""}}));
}

TEST(lexer, empty2)
{
	char *input = "  ";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result, {{TK_EOF, ""}}));
}

TEST(lexer, subshell)
{
	char *input = "(cmd)";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_LPAREN, "("},
		{TK_WORD, "cmd"},
		{TK_RPAREN, ")"},
		{TK_EOF, ""}}));
}

// semicolon
TEST(lexer, semicolon)
{
	char *input = "cmd1;cmd2;cmd3";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "cmd1"},
		{TK_SEMICOLON, ";"},
		{TK_WORD, "cmd2"},
		{TK_SEMICOLON, ";"},
		{TK_WORD, "cmd3"},
		{TK_EOF, ""}}));
}

// and, semicolon
TEST(lexer, and_semicolon)
{
	char *input = "cmd1&&cmd2;cmd3";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "cmd1"},
		{TK_AND, "&&"},
		{TK_WORD, "cmd2"},
		{TK_SEMICOLON, ";"},
		{TK_WORD, "cmd3"},
		{TK_EOF, ""}}));
}

// pipe, semicolon
TEST(lexer, pipe_semicolon)
{
	char *input = "cmd1|cmd2;cmd3";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "cmd1"},
		{TK_PIPE, "|"},
		{TK_WORD, "cmd2"},
		{TK_SEMICOLON, ";"},
		{TK_WORD, "cmd3"},
		{TK_EOF, ""}}));
}

// subshell, semicolon
TEST(lexer, subshell_semicolon)
{
	char *input = "(cmd1);cmd2";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_LPAREN, "("},
		{TK_WORD, "cmd1"},
		{TK_RPAREN, ")"},
		{TK_SEMICOLON, ";"},
		{TK_WORD, "cmd2"},
		{TK_EOF, ""}}));
}

// semicolon in subshell
TEST(lexer, semicolon_in_subshell)
{
	char *input = "(cmd1;cmd2)";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_LPAREN, "("},
		{TK_WORD, "cmd1"},
		{TK_SEMICOLON, ";"},
		{TK_WORD, "cmd2"},
		{TK_RPAREN, ")"},
		{TK_EOF, ""}}));
}

TEST(lexer, back_slash)
{
	char *input = "\\";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "\\"},
		{TK_EOF, ""}}));
}

TEST(lexer, escape_single_quote1)
{
	char *input = "\\'"; // \'
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "\\'"},
		{TK_EOF, ""}}));
}

TEST(lexer, escape_single_quote2)
{
	char *input = "\\'&& \\'"; // \'&& \'
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "\\'"},
		{TK_AND, "&&"},
		{TK_WORD, "\\'"},
		{TK_EOF, ""}}));
}

TEST(lexer, back_slash_in_single_quote)
{
	char *input = "'\\' hello";
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "'\\'"},
		{TK_WORD, "hello"},
		{TK_EOF, ""}}));
}

TEST(lexer, escape_double_quote)
{
	char *input = "\\\""; // \"
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "\\\""},
		{TK_EOF, ""}}));

}

TEST(lexer, escape_double_quote2)
{
	char *input = "\\\"&& \\\""; // \"&& \"
	auto	ctx = Context().getCtx();
	t_token_stream *result;
	tokenize(input, &result, ctx);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(compareTokenStream(result,
		{{TK_WORD, "\\\""},
		{TK_AND, "&&"},
		{TK_WORD, "\\\""},
		{TK_EOF, ""}}));
}