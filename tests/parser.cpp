#include <gtest/gtest.h>
#include "ast.h"
#include "utils/ast_builder.hpp"

extern "C" {
#include "parser_internal.h"
#include "parser.h"
}

TEST(parser, normal)
{
	char *input = "ls";
	auto result = parse(input);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("ls");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, pipe)
{
	char *input = "ls | ls | ls";
	auto result = parse(input);
	auto expected = ASTBuilder(N_PIPE)
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("ls")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("ls")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("ls");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect)
{
	char *input = "cat > file1 < file2 >> file3";
	auto result = parse(input);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("cat")
		.addRedirect(REDIRECT_OUT, "file1").addRedirect(REDIRECT_IN, "file2").addRedirect(REDIRECT_APPEND, "file3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect2)
{
	char *input = "cat < file1 < file2 < file3";
	auto result = parse(input);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("cat")
		.addRedirect(REDIRECT_IN, "file1").addRedirect(REDIRECT_IN, "file2").addRedirect(REDIRECT_IN, "file3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect3)
{
	char *input = "cat > file1 > file2 > file3";
	auto result = parse(input);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("cat")
		.addRedirect(REDIRECT_OUT, "file1").addRedirect(REDIRECT_OUT, "file2").addRedirect(REDIRECT_OUT, "file3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect4)
{
	char *input = "cat >> file1 >> file2 >> file3";
	auto result = parse(input);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("cat")
		.addRedirect(REDIRECT_APPEND, "file1").addRedirect(REDIRECT_APPEND, "file2").addRedirect(REDIRECT_APPEND, "file3");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, and_or)
{
	char *input = "./cmd1 && cmd2 || /bin/cmd3";
	auto result = parse(input);
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
	char *input = "cmd1 | cmd2 && cmd3 | cmd4";
	auto result = parse(input);
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
	char *input = "cmd1 | cmd2 && cmd3 || cmd4";
	auto result = parse(input);
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
	char *input = "cmd1 > file1 && cmd2";
	auto result = parse(input);
	auto expected = ASTBuilder(N_AND)
		.moveToLeft(N_COMMAND).addArgument("cmd1").addRedirect(REDIRECT_OUT, "file1")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect_before_or)
{
	char *input = "cmd1 > file1 || cmd2";
	auto result = parse(input);
	auto expected = ASTBuilder(N_OR)
		.moveToLeft(N_COMMAND).addArgument("cmd1").addRedirect(REDIRECT_OUT, "file1")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect_before_pipe)
{
	char *input = "cmd1 > file1 | cmd2";
	auto result = parse(input);
	auto expected = ASTBuilder(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("cmd1").addRedirect(REDIRECT_OUT, "file1")
		.moveToRoot()
		.moveToRight(N_COMMAND).addArgument("cmd2");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, pipe_and_or_with_redirect)
{
	char *input = "cmd1 | cmd2 > file1 && cmd3 || cmd4";
	auto result = parse(input);
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
	char *input = "ls | cat > file1 < file2 >> file3 && cmd2 < file4 > file5 || /bin/cmd3 < file6 > file7";
	auto result = parse(input);
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
	char *input = "> a";
	auto result = parse(input);
	auto expected = ASTBuilder(N_COMMAND)
		.addRedirect(REDIRECT_OUT, "a");

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, empty)
{
	char *input = "";
	auto result = parse(input);
	auto expected = ASTBuilder(N_COMMAND);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}

TEST(parser, empty2)
{
	char *input = "  ";
	auto result = parse(input);
	auto expected = ASTBuilder(N_COMMAND);

	EXPECT_NE(result, nullptr);
	ASSERT_TRUE(expected == result);
}
