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

	ASSERT_TRUE(expected == result);
}

TEST(parser, pipe)
{
	char *input = "ls | ls | ls";
	auto result = parse(input);
	auto expected = ASTBuilder(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("ls")
		.moveToParent()
		.moveToRight(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("ls")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("ls");

	ASSERT_TRUE(expected == result);
}

TEST(parser, redirect)
{
	char *input = "cat > file1 < file2 >> file3";
	auto result = parse(input);
	auto expected = ASTBuilder(N_COMMAND)
		.addArgument("cat")
		.addRedirect(REDIRECT_OUT, "file1")
		.addRedirect(REDIRECT_IN, "file2")
		.addRedirect(REDIRECT_APPEND, "file3");

	ASSERT_TRUE(expected == result);
}

TEST(parser, and_or)
{
	char *input = "./cmd1 && cmd2 || /bin/cmd3";
	auto result = parse(input);
	auto expected = ASTBuilder(N_AND)
		.moveToLeft(N_COMMAND).addArgument("./cmd1")
		.moveToParent()
		.moveToRight(N_OR)
		.moveToLeft(N_COMMAND).addArgument("cmd2")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("/bin/cmd3");

	ASSERT_TRUE(expected == result);
}
