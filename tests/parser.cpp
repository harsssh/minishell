#include <gtest/gtest.h>
#include "ast.h"
#include "utils/ast_builder.hpp"

extern "C" {
#include "parser_internal.h"
#include "parser.h"
}

TEST(parser, normal)
{
	auto input = "ls";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("ls");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, pipe)
{
	auto input = "cmd1 | cmd2 | cmd3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_PIPE)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect)
{
	auto input = "cat > file1 < file2 >> file3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("cat")
		.addRedirect(REDIRECT_OUT, "file1").addRedirect(REDIRECT_IN, "file2").addRedirect(REDIRECT_APPEND, "file3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect2)
{
	auto input = "cat < file1 < file2 < file3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("cat")
		.addRedirect(REDIRECT_IN, "file1").addRedirect(REDIRECT_IN, "file2").addRedirect(REDIRECT_IN, "file3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect3)
{
	auto input = "cat > file1 > file2 > file3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("cat")
		.addRedirect(REDIRECT_OUT, "file1").addRedirect(REDIRECT_OUT, "file2").addRedirect(REDIRECT_OUT, "file3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect4)
{
	auto input = "cat >> file1 >> file2 >> file3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("cat")
		.addRedirect(REDIRECT_APPEND, "file1").addRedirect(REDIRECT_APPEND, "file2").addRedirect(REDIRECT_APPEND, "file3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, and_or)
{
	auto input = "./cmd1 && cmd2 || /bin/cmd3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_OR)
		.moveToLeft(N_AND)
		.moveToLeft(N_COMMAND).addArgument("./cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("/bin/cmd3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, pipe_and_pipe)
{
	auto input = "cmd1 | cmd2 && cmd3 | cmd4";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_AND)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToRoot()
		.moveToRight(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd3")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd4");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, pipe_and_or)
{
	auto input = "cmd1 | cmd2 && cmd3 || cmd4";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_OR)
		.moveToLeft(N_AND)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToParent()
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd3")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd4");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect_before_and)
{
	auto input = "cmd1 > file1 && cmd2";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_AND)
		.moveToLeft(N_COMMAND).addArgument("cmd1").addRedirect(REDIRECT_OUT, "file1")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect_before_or)
{
	auto input = "cmd1 > file1 || cmd2";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_OR)
		.moveToLeft(N_COMMAND).addArgument("cmd1").addRedirect(REDIRECT_OUT, "file1")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect_before_pipe)
{
	auto input = "cmd1 > file1 | cmd2";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1").addRedirect(REDIRECT_OUT, "file1")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, pipe_and_or_with_redirect)
{
	auto input = "cmd1 | cmd2 > file1 && cmd3 || cmd4";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_OR)
		.moveToLeft(N_AND)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2").addRedirect(REDIRECT_OUT, "file1")
		.moveToParent()
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd3")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd4");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, go_crazy)
{
	auto input = "ls | cat > file1 < file2 >> file3 && cmd2 < file4 > file5 || /bin/cmd3 < file6 > file7";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_OR)
		.moveToLeft(N_AND)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("ls")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cat").addRedirect(REDIRECT_OUT, "file1").addRedirect(REDIRECT_IN, "file2").addRedirect(REDIRECT_APPEND, "file3")
		.moveToParent()
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2").addRedirect(REDIRECT_IN, "file4").addRedirect(REDIRECT_OUT, "file5")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("/bin/cmd3").addRedirect(REDIRECT_IN, "file6").addRedirect(REDIRECT_OUT, "file7");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, only_redirect)
{
	auto input = "> a";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND)
		.addRedirect(REDIRECT_OUT, "a");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect_both)
{
	auto input = "> a < b";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND)
		.addRedirect(REDIRECT_OUT, "a")
		.addRedirect(REDIRECT_IN, "b");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect_cmd_redirect)
{
	auto input = "> out cmd < in";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND).addArgument("cmd").addRedirect(REDIRECT_OUT, "out") .addRedirect(REDIRECT_IN, "in");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, empty)
{
	auto input = "";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser, empty2)
{
	auto input = "  ";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser, subshell)
{
	auto input = "(cmd)";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SUBSHELL)
		.moveToLeft(N_COMMAND).addArgument("cmd");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect_in_subshell)
{
	auto input = "(> out cmd < in)";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SUBSHELL)
		.moveToLeft(N_COMMAND).addArgument("cmd").addRedirect(REDIRECT_OUT, "out").addRedirect(REDIRECT_IN, "in");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, pipe_in_subshell)
{
	auto input = "(cmd1 | cmd2)";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SUBSHELL)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, and_in_subshell)
{
	auto input = "(cmd1 && cmd2)";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SUBSHELL)
		.moveToLeft(N_AND)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, subshell_piped)
{
	auto input = "(cmd1 | cmd2) | cmd3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_PIPE)
		.moveToLeft(N_SUBSHELL)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, subshell_piped2)
{
	auto input = "cmd1 | (cmd2 | cmd3)";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToRoot()
		.moveToRight(N_SUBSHELL)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd2")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, subshell_piped3)
{
	auto input = "(cmd1 | cmd2) | (cmd3 | cmd4)";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_PIPE)
		.moveToLeft(N_SUBSHELL)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToRoot()
		.moveToRight(N_SUBSHELL)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd3")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd4");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, subshell_and_subshell)
{
	auto input = "(cmd1 && cmd2) && (cmd3 && cmd4)";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_AND)
		.moveToLeft(N_SUBSHELL)
		.moveToLeft(N_AND)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToRoot()
		.moveToRight(N_SUBSHELL)
		.moveToLeft(N_AND)
		.moveToLeft(N_COMMAND).addArgument("cmd3")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd4");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, subshell_redirect)
{
	auto input = "(cmd1) > file1 < file2 >> file3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SUBSHELL).addRedirect(REDIRECT_OUT, "file1").addRedirect(REDIRECT_IN, "file2").addRedirect(REDIRECT_APPEND, "file3")
		.moveToLeft(N_COMMAND).addArgument("cmd1");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, subshell_in_subshell)
{
	auto input = "((cmd1))";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SUBSHELL)
		.moveToLeft(N_SUBSHELL)
		.moveToLeft(N_COMMAND).addArgument("cmd1");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, subshell_in_subshell2)
{
	auto input = "((cmd1 | cmd2) | cmd3) | cmd4";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_PIPE)
		.moveToLeft(N_SUBSHELL)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_SUBSHELL)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToParent()
		.moveToParent()
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd3")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd4");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, subshell_with_space)
{
	auto input = "(  cmd1  )";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SUBSHELL)
		.moveToLeft(N_COMMAND).addArgument("cmd1");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

// semicolon
TEST(parser, semicolon)
{
	auto input = "cmd1; cmd2";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SEMICOLON)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

// and, semicolon
TEST(parser, and_semicolon)
{
	auto input = "cmd1 && cmd2; cmd3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SEMICOLON)
		.moveToLeft(N_AND)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

// pipe, semicolon
TEST(parser, pipe_semicolon)
{
	auto input = "cmd1 | cmd2; cmd3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SEMICOLON)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

// subshell, semicolon
TEST(parser, subshell_semicolon)
{
	auto input = "(cmd1); cmd2";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SEMICOLON)
		.moveToLeft(N_SUBSHELL)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

// semicolon in subshell
TEST(parser, semicolon_in_subshell)
{
	auto input = "(cmd1; cmd2)";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SUBSHELL)
		.moveToLeft(N_SEMICOLON)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent() // N_SEMICOLON
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

// semicolon, semicolon
TEST(parser, semicolon_semicolon)
{
	auto input = "cmd1; cmd2; cmd3";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_SEMICOLON)
		.moveToLeft(N_SEMICOLON)
		.moveToLeft(N_COMMAND).addArgument("cmd1")
		.moveToParent() // N_SEMICOLON
		.moveToRight(N_COMMAND).addArgument("cmd2")
		.moveToRoot() // N_SEMICOLON (root)
		.moveToRight(N_COMMAND).addArgument("cmd3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

// tail semicolon
TEST(parser, tail_semicolon)
{
	auto input = "cmd1;";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND).addArgument("cmd1");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, escape_single_quote)
{
	auto input = "\\'";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND).addArgument("\\'");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, escape_double_quote)
{
	auto input = "\\\"";
	auto result = parse(input, nullptr);
	auto expected = ASTBuilder(N_COMMAND).addArgument("\\\"");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

/* 異常系 */
TEST(parser_negative, no_command)
{
	auto input = "|";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, no_command2)
{
	auto input = ">";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, no_command3)
{
	auto input = "&&";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, incomplete)
{
	auto input = "cmd |";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, incomplete2)
{
	auto input = "cmd >";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, incomplete3)
{
	auto input = "cmd &&";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

// 特殊なトークンが連続する
TEST(parser_negative, consecutive_special_token)
{
	auto input = "cmd1 && | cmd2";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, consecutive_special_token2)
{
	auto input = "cmd1 && && cmd2";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, unknown_token)
{
	auto input = "cmd >>> file";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

// here-string
TEST(parser_negative, not_supported)
{
	auto input = "cmd <<< string";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, not_supported2)
{
	auto input = "cmd <> file";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, not_supported3)
{
	auto input = "cmd >| file";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, redirect_before_subshell)
{
	auto input = "> file (cmd)";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, consecutive_subshell)
{
	auto input = "(cmd1) (cmd2)";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, incomplete_subshell)
{
	auto input = "(cmd1";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, incomplete_subshell2)
{
	auto input = "cmd1)";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}

TEST(parser_negative, incomplete_escape)
{
	auto input = "\\";
	auto result = parse(input, nullptr);

	EXPECT_EQ(result, nullptr);
}